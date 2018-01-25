# -*- coding: utf-8 -*-
import os
import sys
import time
import math
import random
import sqlite3

sys.path.append('../distributions')
sys.path.append('../model')
import pwl
from pwl import PWL
from models import Store

ent_size = {}

# id start at 1, and do not need to compelte it, for example: 
# 1, 2, 3, .., 10, .., 999
# do not need like this: 001, 002, ... 999

def pre_deal(ents):
  for ent in ents:
    ent_size[ent['alias']] = int(ent['ceiling'])


# send msg by Pipe
# data type: [(, , ), ...]
def gen_fixed_ent(ent, child_conn):
  name  = ent['alias']
  count = ent['ceiling']
  msg   = [()] * count
  if 'tag' in ent:
    for i in range(1, count+1):
      _id = name + str(i)
      _tag = ''
      if ent['tag']['mode'] == 'random':
        n = random.randint(ent['tag']['count'][0], ent['tag']['count'][1])
        b = len(ent['tag']['source']) - 1
        t_ent = ent['tag']['source'][random.randint(0, b)]
        t_upp = ent_size[t_ent]
        _tag  = t_ent + str(random.randint(1, t_upp))
        for j in range(n-1):
          t_ent = ent['tag']['source'][random.randint(0, b)]
          t_upp = ent_size[t_ent]
          _tag  = _tag + ' ' + t_ent + str(random.randint(1, t_upp))
      elif ent['tag']['mode'] == 'exclusive':
        b = len(ent['tag']['source'])
        l = min(b, min(ent['tag']['count']))
        r = min(b, max(ent['tag']['count']))
        n = random.randint(l, r)
        p = [x for x in range(b)]
        if n > 0:
          t_ent = ent['tag']['source'][p[0]]
          t_upp = ent_size[t_ent]
          _tag  = t_ent + str(random.randint(1, t_upp))
        for j in range(1, n):
          t_ent = ent['tag']['source'][p[j]]
          t_upp = ent_size[t_ent]
          _tag  = _tag + ' ' + t_ent + str(random.randint(1, t_upp))
      else: # respective
        for t_ent in ent['tag']['source']:
          t_upp = ent_size[t_ent]
          l     = min(t_upp, min(ent['tag']['count']))
          r     = min(t_upp, max(ent['tag']['count']))
          n     = random.randint(l, r)
          tp_set = set()
          for i in range(n):
            while True:
              res = random.randint(1, t_upp)
              if res not in tp_set:
                break
            tp_set.add(res)
            _tag = _tag + ' ' + t_ent + str(res)
      msg[i] = (_id, _tag)
  else:
    for i in range(1, count+1):
      msg[i] = (name + str(i),)
  child_conn.send(msg)


class GenFFR(object):
  '''
  generate relation: src -> tag
  src is fixed, and tag is fixed
  '''
  def __init__(self, src_conn, tgt_conn):
    self.src_conn = src_conn
    self.tgt_conn = tgt_conn
    self.in_degree_nums  = []
    self.out_degree_nums = []
    self.node_in_degree  = []
    self.node_out_degree = []
    self.msg_send = []
    self.msg_recv = []


class GenFDR(object):
  '''
  src is fixed, but tag is dynamic
  '''
  def __init__(self, src_conn, tgt_conn):
    self.src_conn = src_conn
    self.tgt_conn = tgt_conn
    self.in_degree_nums  = []
    self.out_degree_nums = []
    self.node_in_degree  = []
    self.node_out_degree = []
    self.msg_send = []
    self.msg_recv = []


class GenDFR(object):
  '''
  src is dynamic, but tag is fixed
  '''
  def __init__(self, src_conn, tgt_conn):
    self.src_conn = src_conn
    self.tgt_conn = tgt_conn
    self.in_degree_nums  = []
    self.out_degree_nums = []
    self.node_in_degree  = []
    self.node_out_degree = []
    self.msg_send = []
    self.msg_recv = []


class GenDDR(object):
  '''
  src is dynamic, and tag is dynamic
  '''
  def __init__(self, parent_conn, src_conn, tgt_conn, dic, db):
    '''
    src_conn: used to recv and send data from src entity process
    tgt_conn: ditto, from tgt entity process
    dict    : the relation dict of the config
    '''
    self.parent_conn = parent_conn
    self.src_conn = src_conn
    self.tgt_conn = tgt_conn
    self.rel_dict = dic
    self.db_name  = db
    self.db_handler  = Store(db)
    db_handler.connect()
    # remain the pwl info ???
    self.convert = False
    if isinstance(dic['in']['lambd'], int):
      self.tau  = dic['in']['lambd']
      self.tau1 = dic['out']['lambd'][0]
      self.tau2 = dic['out']['lambd'][1]
    else:
      self.convert = True
      self.tau  = dic['out']['lambd']
      self.tau1 = dic['in']['lambd'][0]
      self.tau2 = dic['in']['lambd'][1]
    # some statistical info
    self.in_degree_nums  = []   # [i] : the number of nodes with int degree i
    self.out_degree_nums = []   # [i] : the number of nodes with out degree i 
    self.node_in_degree  = []   # [i] : the in degree of node i
    self.node_out_degree = []   # [i] : the out degree of node i
    self.in_degree_nodes  = []  # [i] : the nodes with in degree i
    self.out_degree_nodes = []  # [i] : the nodes with out degree i
    # related to recv and send data
    self.msg_send = []          # [tuples]
    self.msg_recv = []          # [tuples]
    self.poll_delay = 0         # time between recving data
    # generate index and nums info
    self.src_node_cnt = 0
    self.tgt_node_cnt = 0
    self.src_fake_cnt = 0
    self.tgt_fake_cnt = 0 
    # compress degree list, to accelerate
    self.step = 1 # TODO: config info, compress step
    self.pwl_instance = PWL(0, tau, tau1, tau2)

  def polling(self):
    while True:
      src_nodes = self.src_conn.recv()
      tag_nodes = self.tgt_conn.recv()
      assert isinstance(src_nodes, list)
      assert isinstance(tag_nodes, list)
      if src_nodes[0] == 'terminate' or tag_nodes[0] == 'terminate':
        # send info to parent process
        self.parent_conn.send((0, [])) # means generate edges terminated.
        # send end
        break
      self.gen_data(src_nodes, tag_nodes)
      time.sleep(self.poll_delay)
    self.db_handler.close()

  def build_vector(self, a, b, mx_dgre, dlt_dgre, dgre_nodes):
    '''
    a, b     : generate interval [a, b)
    mx_dgre  : max degree
    dlt_dgre : delta_in_degree or delta_out_degree
    dgre_nodes: in_degree_nodes or out_degree_nodes
    return: (0/1, extra_nodes, rtn_vector)
            0: do not need to add edges, 1: in contrast
    '''
    extra_nodes = 0
    minus = 0
    for i in range(len(dlt_dgre)):
      if dlt_dgre[i] < 0:
        dlt_dgre[i] = 0
        minus += 1
      elif dlt_dgre[i] == 0:
        minus += 1
    if minus > (len(dlt_dgre) / 3): # TODO: set parameter
      return (0, extra_nodes, [])
    # compute new node
    end_i = b
    new = [i for i in range(a, b)]
    random.shuffle(new)
    # compute compress degree list
    cmprs_dgre = []
    ii = 0
    for i in range(int(math.floor(mx_dgre / self.step))):
      s = 0
      for j in range(i*self.step, i*self.step + self.step):
        s += dlt_dgre[j]
      cmprs_dgre.append(s)
      ii = i
    s = 0
    for j in range(ii*self.step + self.step, mx_dgre):
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
      # curcial part: adjust the compress degree list
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
            more = max(comp_size - (end_i - new_i), 0)
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
        # 
        new_i = 0
        for i in range(delta_len):
          rtn_vector += new[new_i:new_i + cmprs_dgre[i]] * (self.step * (i + 1))
          new_i += cmprs_dgre[i]
        # 
        j = 0
        for i in range(delta_len, len(cmprs_dgre)):
          comp_size = cmprs_dgre[i] - len(dgre_nodes[j])
          rtn_vector += dgre_nodes[j][:cmprs_dgre[i]] * (self.step * delta_len)
          if comp_size > 0:
            more = max(comp_size - (end_i - new_i), 0)
            new += [i for i in range(end_i, end_i + more)]
            extra_nodes += more
            end_i += more
            rtn_vector += new[new_i:new_i + comp_size] * (self.step * (i + 1))
            new_i += comp_size
          j += 1
    return (1, extra_nodes, rtn_vector)

  def add_edge_info(self, src_id, tgt_id, out_i, in_i):
    sql = 'select * from %s where src_id = %s and tgt_id = %s' % (self.rel_dict['alias'], src_id, tgt_id)
    res = db_handler.query(sql)
    if len(res) == 0:
      # deal with sth about out degree
      for i in range(len(self.node_out_degree), out_i + 1):
        self.node_out_degree.append(0)
      self.node_out_degree[out_i] += 1
      degreei = self.node_out_degree[out_i]
      ind  = int(degreei / self.step)
      ind_ = int((degreei - 1) / self.step)
      if self.step == 1:
        ind  -= 1
        ind_ -= 1
      for i in range(len(self.out_degree_nodes), ind + 1):
        self.out_degree_nodes.append([])
        self.out_degree_nums.append(0)
      if degreei == 1:
        self.out_degree_nodes[0].append(out_i)
        self.out_degree_nums[0] += 1
      elif degreei % self.step == 0:
        try:
          self.out_degree_nodes[ind_].remove(out_i)
          self.out_degree_nums[ind_] -= 1
        except Exception as e:
          pass
        self.out_degree_nodes[ind].append(out_i)
        self.out_degree_nums[ind] += 1
      # deal with sth about in degree
      for i in range(len(self.node_in_degree), in_i + 1):
        self.node_in_degree.append(0)
      self.node_in_degree[in_i] += 1
      degreei = self.node_in_degree[in_i]
      ind  = int(degreei / self.step)
      ind_ = int((degreei - 1) / self.step)
      if self.step == 1:
        ind  -= 1
        ind_ -= 1
      for i in range(len(self.in_degree_nodes), ind + 1):
        self.in_degree_nodes.append([])
        self.in_degree_nums.append(0)
      if degreei == 1:
        self.in_degree_nodes[0].append(in_i)
        self.in_degree_nums[0] += 1
      elif degreei % self.step == 0:
        try:
          self.in_degree_nodes[ind_].remove(in_i)
          self.in_degree_nums[ind_] -= 1
        except Exception as e:
          pass
        self.in_degree_nodes[ind].append(in_i)
        self.in_degree_nums[ind] += 1

  def gen_data(self, src_nodes, tag_nodes):
    '''
    need to send msg to parent process
    content: (flag, extra)
            flag:  0 means do not need to add edges, while 1 means have added edges
            extra: when flag == 1, need to generate more nodes (extra)
    '''
    lens = src_nodes[1] - src_nodes[0]
    lent = tag_nodes[1] - tag_nodes[0]
    self.src_fake_cnt += lens
    self.tgt_fake_cnt += lent
    rel_data = []
    if isinstance(self.dic['in']['lambd'], int):
      # compute in vector
      self.pwl_instance.set_nodes(self.tgt_fake_cnt)
      self.pwl_instance.dtmn_max_degree()
      max_in_degree = self.pwl_instance.max_d1
      cur_in_degree = pwl.get_node_count(self.tgt_fake_cnt, max_in_degree, self.tau)
      delta = max_in_degree - len(self.in_degree_nums)
      last_in_degree = self.in_degree_nums[:] + [0] * delta
      delta_in_degree = []
      for i in range(len(cur_in_degree)):
        delta_in_degree[i] = cur_in_degree[i] - last_in_degree[i]
      (flag, extra_in, in_vector) = self.build_vector(src_nodes[0], src_nodes[1], max_in_degree, delta_in_degree, self.in_degree_nodes)
      if flag == 0:
        # : return sth
        self.src_conn.send((0, 0))
        self.tgt_conn.send((0, 0))
        self.src_fake_cnt -= lens
        self.tgt_fake_cnt -= lent
        return
      # do not need to send extra data
      # compute out vector
      self.pwl_instance.set_nodes(self.src_fake_cnt)
      self.pwl_instance.dtmn_max_degree()
      maxk1, maxk2, cur_out_degree = self.pwl_instance.dtmn_max_degree_2()
      delta = len(cur_out_degree) - len(self.out_degree_nums)
      last_out_degree = self.out_degree_nums[:] + [0] * delta
      delta_out_degree = []
      for i in range(len(cur_out_degree)):
        delta_out_degree[i] = cur_out_degree[i] - last_out_degree[i]
      (flag, extra_out, out_vector) = self.build_vector(tag_nodes[0], tag_nodes[1], maxk2, delta_out_degree, self.out_degree_nodes)
      if flag == 0:
        # : return sth
        self.src_conn.send((0, 0))
        self.tgt_conn.send((0, 0))
        self.src_fake_cnt -= lens
        self.tgt_fake_cnt -= lent
        return
      # do not need to send extra data
    else:
      # compute out vector
      self.pwl_instance.set_nodes(self.src_fake_cnt)
      self.pwl_instance.dtmn_max_degree()
      max_out_degree = self.pwl_instance.max_d1
      cur_out_degree = pwl.get_node_count(self.src_fake_cnt, max_out_degree, self.tau)
      delta = max_out_degree - len(self.out_degree_nums)
      last_out_degree = self.out_degree_nums[:] + [0] * delta
      delta_out_degree = []
      for i in range(len(cur_out_degree)):
        delta_out_degree[i] = cur_out_degree[i] - last_out_degree[i]
      (flag, extra_out, out_vector) = self.build_vector(tag_nodes[0], tag_nodes[1], max_out_degree, delta_out_degree, self.out_degree_nodes)
      if flag == 0:
        # : return sth
        self.src_conn.send((0, 0))
        self.tgt_conn.send((0, 0))
        self.src_fake_cnt -= lens
        self.tgt_fake_cnt -= lent
        return
      # do not need to send extra data
      # compute out vector
      self.pwl_instance.set_nodes(self.tgt_fake_cnt)
      self.pwl_instance.dtmn_max_degree()
      maxk1, maxk2, cur_in_degree = self.pwl_instance.dtmn_max_degree_2()
      delta = len(cur_in_degree) - len(self.in_degree_nums)
      last_in_degree = self.in_degree_nums[:] + [0] * delta
      delta_in_degree = []
      for i in range(len(cur_in_degree)):
        delta_in_degree[i] = cur_in_degree[i] - last_in_degree[i]
      (flag, extra_in, in_vector) = self.build_vector(src_nodes[0], src_nodes[1], maxk2, delta_in_degree, self.in_degree_nodes)
      if flag == 0:
        # : return sth
        self.src_conn.send((0, 0))
        self.tgt_conn.send((0, 0))
        self.src_fake_cnt -= lens
        self.tgt_fake_cnt -= lent
        return
      # do not need to send extra data
    # send to entity process the info
    self.src_conn.send((1, extra_out))
    self.tgt_conn.send((1, extra_in))
    # send end
    # generate edges
    in_remain  = []
    out_remain = []
    random.shuffle(in_vector)
    random.shuffle(out_vector)
    upper = min(len(in_vector), len(out_vector))
    for i in range(upper):
      if in_vector[i] != out_vector[i]:
        src_id = self.rel_dict['source'] + str(out_vector[i])
        tgt_id = self.rel_dict['target'] + str(in_vector[i])
        if (src_id, tgt_id) in rel_data:
          continue
        self.add_edge_info(src_id, tgt_id, out_vector[i], in_vector[i])
        rel_data.append((src_id, tgt_id))
      else:
        out_remain.append(out_vector[i])
        in_remain.append(in_vector[i])
    while True:
      threshold = len(out_remain)
      remain_out = []
      remain_in  = []
      random.shuffle(out_remain)
      random.shuffle(in_remain)
      for i in range(len(out_remain)):
        if out_remain[i] != in_remain[i]:
          src_id = self.rel_dict['source'] + str(out_remain[i])
          tgt_id = self.rel_dict['target'] + str(in_remain[i])
          if (src_id, tgt_id) in rel_data:
            continue
          self.add_edge_info(src_id, tgt_id, out_remain[i], in_remain[i])
          rel_data.append((src_id, tgt_id))
        else:
          remain_out.append(out_remain[i])
          remain_in.append(in_remain[i])
      if len(remain_in) == 0 or len(remain_in) == threshold:
        break
      out_remain = remain_out
      in_remain  = remain_in
    # generate end
    # send info to parent process
    self.parent_conn.send((1, rel_data))
    # send end

def test():
  pass


if __name__ == '__main__':
  test()
