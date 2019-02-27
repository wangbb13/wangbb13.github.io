# -*- coding: utf-8 -*-
# python3
import sys 
sys.path.append('../')

# from test import test_scheme
from model import Store
from distributions import pwl, PWL
import math
from scipy import stats

class Analyses(object):
  '''
  Analyse data quality generated by our generator
  '''
  def __init__(self, dic, db, in_, out, cutoff=6):
    '''
    dic: the dict info of one type edge 
    db : db file name, store the generated graph data
    '''
    self.rel_dict = dic
    self.db_name  = db
    self.db_handler = Store(db)
    self.db_handler.connect()
    self.cutoff = cutoff
    self.in_cnt = in_ 
    self.out_cnt = out


  def statistic(self, array):
    '''
    array: 
    '''
    array = sorted(array)
    n = len(array)
    an_dic = {}
    i = 0
    size = 0
    while i < n:
      j = 1
      while i+1 < n and array[i] == array[i+1]:
        i += 1
        j += 1
      i += 1
      size = max(size, j)
      if j in an_dic:
        an_dic[j] += 1
      else:
        an_dic[j] = 1

    size += 1
    ans = [0] * size 
    for i in range(size):
      if i in an_dic:
        ans[i] = an_dic[i]
    
    i = size - 1
    while i > 0:
      if ans[i] < self.cutoff:
        i -= 1
        continue
      else:
        break
    self.cutted_len = i 
    return ans[1:self.cutted_len+1]


  def get_data(self):
    try:
      rel_name = self.rel_dict['alias']
      src_name = self.rel_dict['source']
      tgt_name = self.rel_dict['target']
      sql_cntsrc = 'select count(*) from %s' % (src_name)
      sql_cnttgt = 'select count(*) from %s' % (tgt_name)
      sql_all = 'select * from %s' % (rel_name)
      # self.out_cnt = self.db_handler.query(sql_cntsrc)[0][0]
      # self.in_cnt = self.db_handler.query(sql_cnttgt)[0][0]
      res_all = self.db_handler.query(sql_all)
      out_array = [t[0] for t in res_all]
      in_array  = [t[1] for t in res_all]
      return (out_array, in_array)
    except Exception as e:
      raise e
    finally:
      self.db_handler.close()


  def analyse(self):
    try:
      out_array, in_array = self.get_data()
      if isinstance(self.rel_dict['in']['lambd'], list):
        tau = self.rel_dict['out']['lambd']
        tau1 = self.rel_dict['in']['lambd'][0]
        tau2 = self.rel_dict['in']['lambd'][1]
        one = 'out'
        two = 'in'
      else:
        tau = self.rel_dict['in']['lambd']
        tau1 = self.rel_dict['out']['lambd'][0]
        tau2 = self.rel_dict['out']['lambd'][1]
        one = 'in'
        two = 'out'
      pwl_ins = PWL(self.out_cnt, tau, tau1, tau2)
      # analyse one lambd
      node_count = eval('self.%s_cnt' % (one))
      pwl_ins.set_nodes(node_count)
      o_list = self.statistic(eval(one + '_array'))
      pwl_ins.dtmn_max_degree()
      max_degree = pwl_ins.max_d1
      e_list = pwl.get_node_count(node_count, max_degree, tau)[:self.cutted_len]
      if self.cutted_len > len(e_list):
        o_list = o_list[:len(e_list)]
      # improve effect of hypothesis test
      cut_e = len(e_list) - 1
      while cut_e > 0:
        if e_list[cut_e] < self.cutoff:
          cut_e -= 1
        else:
          break
      o_list = o_list[:cut_e+1]
      e_list = e_list[:cut_e+1]
      # end improve
      # leisi facha
      eva_val = math.sqrt(sum(list(map(lambda x: ((x[0]-x[1])**2), list(zip(o_list, e_list))))))
      print('%s Euclidean D: %f' % (one, eva_val))
      one_pvalue = stats.chisquare(o_list, e_list).pvalue
      print('%s Chi-Square : %f' % (one, one_pvalue))
      # analyse two lambd
      node_count = eval('self.%s_cnt' % (two))
      pwl_ins.set_nodes(node_count)
      o_list = self.statistic(eval(two + '_array'))
      pwl_ins.dtmn_max_degree()
      _, _, e_list = pwl_ins.dtmn_max_degree_2()
      e_list = e_list[:self.cutted_len]
      if self.cutted_len > len(e_list):
        o_list = o_list[:len(e_list)]
      # improve effect of hypothesis test
      cut_e = len(e_list) - 1
      while cut_e > 0:
        if e_list[cut_e] < self.cutoff:
          cut_e -= 1
        else:
          break
      o_list = o_list[:cut_e+1]
      e_list = e_list[:cut_e+1]
      # end improve
      # leisi facha
      eva_val = math.sqrt(sum(list(map(lambda x: ((x[0]-x[1])**2), list(zip(o_list, e_list))))))
      print('%s Euclidean D: %f' % (two, eva_val))
      two_pvalue = stats.chisquare(o_list, e_list).pvalue
      print('%s Chi-Square : %f' % (two, two_pvalue))
      return {one: one_pvalue, two: two_pvalue}
    except Exception as e:
      raise e


class LFRAnalyses(object):
  # TODO
  pass


class GMarkAnalyses(object):
  # TODO
  pass
