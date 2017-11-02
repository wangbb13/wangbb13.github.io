# -*- coding: utf-8 -*-
import os
import sys
import time
import math
import random
from datetime import datetime, timedelta

sys.path.append('../distributions')
import pwl
from pwl import PWL

feed_handler = open('feed.txt', 'w')
cmt_handler  = open('comment.txt', 'w')
thm_handler  = open('thumbup.txt', 'w')

user_ceiling = 100000
cmt_tau      = 1.71
thmb_up_tau  = 1.62

gen_start_time = datetime(2017, 10, 20, 0, 0, 0)
day = [
{'mu': 2, 'sigma': 5, 'hours': 5},    # 00:00 - 05:00
{'mu': 10, 'sigma': 2, 'hours': 4},   # 05:00 - 09:00
{'mu': 90, 'sigma': 10, 'hours': 3},  # 09:00 - 12:00
{'mu': 140, 'sigma': 13, 'hours': 2}, # 12:00 - 14:00
{'mu': 80, 'sigma': 15, 'hours': 4},  # 14:00 - 18:00
{'mu': 70, 'sigma': 9, 'hours': 3},   # 18:00 - 21:00
{'mu': 60, 'sigma': 16, 'hours': 3}   # 21:00 - 24:00
]

alphabet = list('0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_.,?!~@#$%^&*()+-*/;')
al_len   = len(alphabet)
cad_cmt_cnt = len(open('cad_comments.txt', 'r').readlines())
cad_sta_cnt = len(open('cad_status.txt', 'r').readlines())
def gen_content():
  # TODO: better
  # size = random.randint(1, 20)
  # random.shuffle(alphabet)
  # return ''.join(alphabet[:size])
  return str(random.randint(1, cad_sta_cnt))

def gen_comment():
  # TODO: better
  # return gen_content()
  return str(random.randint(1, cad_cmt_cnt))

# input  : gen n status
# method : select n users randomly
# output : [(user_id, status_id), ...] (no prefix)
class GenFeed(object):
  def __init__(self, src_ceiling):
    self.src_num = src_ceiling
    self.tgt_l = 1
    self.tgt_r = 1
    self.src_nodes = [i for i in range(1, src_ceiling + 1)]

  # return: [(src_name : id, tgt_name : id)]
  def gen(self, n):
    self.tgt_r += n 
    random.shuffle(self.src_nodes)
    res_s = [self.src_nodes[si] for si in range(n)]
    res_t = [ti for ti in range(self.tgt_l, self.tgt_r)]
    self.tgt_l = self.tgt_r
    return list(zip(res_s, res_t))


# input  : gen n status
# method : use previous method to ensure power law distribution
# output : [(status_id, cmt_id), ...], extra_status (no prefix)
#       or [(status_id, _)], extra_status (no prefix)
class GenCMTumbUp(object):
  def __init__(self, src_tau):
    '''
    src_tau: out distribution accord with pwl distribution
    '''
    self.src_l = 1 
    self.src_r = 1 
    self.src_num = 0
    self.src_tau = src_tau 
    self.out_degree_nums = []
    self.node_out_degree = []
    self.out_degree_nodes = []
    self.pwl_ins = PWL(0, src_tau)
    self.step = 1

  def set_src(self, l, r, n):
    self.src_l = l 
    self.src_r = r 
    self.src_num = n

  def build_vector(self, a, b, mx_dgre, dlt_dgre, dgre_nodes):
    '''
    parameter explain:
    '''
    extra_nodes = 0 
    minus = 0 
    for i in range(len(dlt_dgre)):
      if dlt_dgre[i] < 0:
        dlt_dgre[i] = 0
      if dlt_dgre[i] == 0:
        minus += 1
    if minus > (len(dlt_dgre) / 3):
      return (0, 0, [])
    # compute new nodes
    end_i = b 
    new = [i for i in range(a, b)]
    random.shuffle(new) 
    # compute compress degree list
    cmprs_dgre = []
    ii = 0 
    for i in range(int(math.floor(mx_dgre / self.step))):
      s = 0 
      for j in range(i * self.step, i * self.step + self.step):
        s += dlt_dgre[j]
      cmprs_dgre.append(s)
      ii = i
    s = 0
    for j in range(ii * self.step + self.step, mx_dgre):
      s += dlt_dgre[j]
    if s != 0:
      cmprs_dgre.append(s)
    # compute rtn vector
    rtn_vector = []
    if len(dgre_nodes) == 0:
      index = 0 
      repeat = 1 
      for num in dlt_dgre:
        rtn_vector += [x for x in new[index:index+num] for j in range(repeat)]
        index += num
        repeat += 1 
    else:
      len_comp  = len(cmprs_dgre)
      len_inot  = len(dgre_nodes)
      delta_len = len_comp - len_inot
      # adjust the compress degree list
      if delta_len <= 0:
        for i in range(len_comp-2, -1, -1):
          cmprs_dgre[i] += cmprs_dgre[i+1]
      else:
        if delta_len >= len_inot:
          for i in range(delta_len, len_comp):
            cmprs_dgre[i - delta_len] += cmprs_dgre[i]
        else:
          for i in range(len_comp - delta_len, len_comp):
            for j in range(i - delta_len, -1, (-delta_len)):
              cmprs_dgre[j] += cmprs_dgre[j + delta_len]
      # add content to rtn vector
      if delta_len <= 0:
        more = max(0, cmprs_dgre[0] - len(new))
        new += [i for i in range(end_i, end_i + more)]
        extra_nodes += more
        end_i += more
        # select nodes from new nodes
        new_i = 0 
        rtn_vector += new[new_i:new_i + cmprs_dgre[0]] * self.step
        new_i += cmprs_dgre[0]
        # select nodes from existing nodes
        j = 0
        for i in range(1, len(cmprs_dgre)):
          comp_size = cmprs_dgre[i] - len(dgre_nodes[j])
          rtn_vector += dgre_nodes[j][:cmprs_dgre[i]] * self.step
          if comp_size > 0:
            more = max(0, comp_size - (end_i - new_i))
            new += [i for i in range(end_i, end_i + more)]
            extra_nodes += more
            end_i += more
            rtn_vector += new[new_i:new_i + comp_size] * (self.step * (i+1))
            new_i += comp_size
          j += 1
      else:
        more = max(0, sum(cmprs_dgre[:delta_len]) - len(new))
        new += [i for i in range(end_i, end_i + more)]
        extra_nodes += more
        end_i += more
        # select nodes from new 
        new_i = 0 
        for i in range(delta_len):
          rtn_vector += new[new_i:new_i + cmprs_dgre[i]] * (self.step * (i + 1))
          new_i += cmprs_dgre[i]
        # select from existing nodes
        j = 0 
        for i in range(delta_len, len(cmprs_dgre)):
          comp_size = cmprs_dgre[i] - len(dgre_nodes[j])
          rtn_vector += dgre_nodes[j][:cmprs_dgre[i]] * (self.step * delta_len)
          if comp_size > 0:
            more = max(0, comp_size - (end_i - new_i))
            new += [i for i in range(end_i, end_i + more)]
            extra_nodes += more
            end_i += more
            rtn_vector += new[new_i:new_i + comp_size] * (self.step * (i + 1))
            new_i += comp_size
          j += 1
    return (1, extra_nodes, rtn_vector)

  def gen(self, n):
    self.src_num += n
    self.src_r   += n
    self.pwl_ins.set_nodes(self.src_num)
    self.pwl_ins.dtmn_max_degree()
    max_out_degree = self.pwl_ins.max_d1
    cur_out_degree = pwl.get_node_count(self.src_num, max_out_degree, self.src_tau)
    delta = max_out_degree - len(self.out_degree_nums)
    last_out_degree = self.out_degree_nums[:] + [0] * delta
    delta_out_degree = []
    for i in range(len(cur_out_degree)):
      delta_out_degree.append(cur_out_degree[i] - last_out_degree[i])
    (flag, extra_out, out_vector) = self.build_vector(self.src_l, self.src_r, max_out_degree, delta_out_degree, self.out_degree_nodes)
    if flag == 0:
      # print(self.src_num, 'flag == 0')
      # self.src_num -= n
      return ([], 0)
    # : adjust sth
    out_i = max(out_vector)
    for i in range(len(self.node_out_degree), out_i + 1):
      self.node_out_degree.append(0)
    for n in out_vector:
      self.node_out_degree[n] += 1
      degreei = self.node_out_degree[n]
      ind  = int(degreei / self.step)
      ind_ = int((degreei - 1) / self.step)
      if self.step == 1:
        ind  -= 1 
        ind_ -= 1
      for i in range(len(self.out_degree_nodes), ind + 1):
        self.out_degree_nodes.append([])
        self.out_degree_nums.append(0)
      if degreei == 1:
        self.out_degree_nodes[0].append(n)
        self.out_degree_nums[0] += 1
      elif degreei % self.step == 0:
        try:
          self.out_degree_nodes[ind_].remove(n)
          self.out_degree_nums[ind_] -= 1
        except Exception as e:
          pass
        self.out_degree_nodes[ind].append(n)
        self.out_degree_nums[ind] += 1
    # : adjust end
    self.src_num += extra_out
    self.src_r += extra_out
    self.src_l = self.src_r
    return (out_vector, extra_out)


def test():
  cur_time = gen_start_time
  now_time = datetime.now()
  gen_feed = GenFeed(user_ceiling)
  gen_cmt  = GenCMTumbUp(cmt_tau)
  gen_thm  = GenCMTumbUp(thmb_up_tau)
  # user_nodes = [i for i in range(1, user_ceiling + 1)]
  sta_idx = 1
  sta_extra = 0
  user_prefix = 'user'
  sta_prefix = 'status'
  # version 1, simple
  try:
    while cur_time < now_time:
      print('[INFO: %s]' % str(cur_time))
      for cfg in day:
        # generate sta_n status
        sta_n = int(random.gauss(cfg['mu'], cfg['sigma']))
        res = gen_feed.gen(sta_n)
        time_r = cfg['hours'] * 3600
        stamp = [str(cur_time + timedelta(0, random.randint(0, time_r))).split('.')[0] \
        for x in range(sta_n)]
        # release status, dump records to txt
        for i in range(sta_n):
          string = user_prefix + str(res[i][0]) + '#' + stamp[i] + '#' + gen_content() + '#' + sta_prefix + str(res[i][1]) + '\n'
          feed_handler.write(string)
        sta_idx += sta_n
        # clear extra status
        sta_extra = 0
        # generate comment
        res, extra = gen_cmt.gen(sta_n)
        sta_extra += extra
        if len(res) > 0:
          # need to add more status, add user -> status
          for i in range(sta_idx, sta_idx + extra):
            string = user_prefix + str(random.randint(1, user_ceiling)) + '#' + \
            str(cur_time + timedelta(0, random.randint(0, time_r))).split('.')[0] + \
            '#' + gen_content() + '#' + sta_prefix + str(i) + '\n'
            feed_handler.write(string)
          for sta_id in res:
            string = sta_prefix + str(sta_id) + '#' + \
            str(cur_time + timedelta(0, random.randint(0, 24*60*60))).split('.')[0] + \
            '#' + gen_comment() + '#' + user_prefix + str(random.randint(1, user_ceiling)) + '\n'
            cmt_handler.write(string)
        sta_idx += extra
        # generate thumbup
        res, extra = gen_thm.gen(sta_n + sta_extra)
        if len(res) > 0:
          # need to add more status, add user -> status
          for i in range(sta_idx, sta_idx + extra):
            string = user_prefix + str(random.randint(1, user_ceiling)) + '#' + \
            str(cur_time + timedelta(0, random.randint(0, time_r))).split('.')[0] + \
            '#' + gen_content() + '#' + sta_prefix + str(i) + '\n'
            feed_handler.write(string)
          for sta_id in res:
            string = sta_prefix + str(sta_id) + '#' + user_prefix + str(random.randint(1, user_ceiling)) + '\n'
            thm_handler.write(string)
        sta_idx += extra
        cur_time = cur_time + timedelta(0, time_r)
  except Exception as e:
    raise e


if __name__ == '__main__':
  test()
