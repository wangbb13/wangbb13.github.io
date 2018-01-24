# -*- coding: utf-8 -*-
import sys
sys.path.append('../')

from distributions import pwl, PWL
from model import Store
from .gen_e import GenFE
import random
import math
import gen.macro


class GenDDR(object):
  '''
  src is dynamic, and tag is dynamic
  '''
  def __init__(self, db, dic, parent_conn, src_dic, ent_size, tgt_dic=None, mode='local'):
    '''
    db: db name
    dic    : the relation dict of the config
    parent_conn: server conn
                 1, rel data
                 2, src nodes: n
                 3, tgt nodes: m
    src_dic: src node config dict
    ent_size: the number of nodes of each entity
    tgt_dic: tgt node config dict
             if is None, then tgt_dic == src_dic, e.g. user -> user
    mode : local (default), dump edge locally
         : u-level, dump edge and node in parent process
    '''
    self.parent_conn = parent_conn
    self.rel_dict = dic
    self.db_name  = db
    self.src_dic = src_dic
    self.tgt_dic = tgt_dic
    self.mode = mode
    self.ent_size = ent_size
    self.db_handler  = Store(db)
    self.db_handler.connect()
    # parameters of power law distribution: 1 - 2
    self.convert = False
    if isinstance(dic['in']['lambd'], list):
      self.tau  = dic['out']['lambd']
      self.tau1 = dic['in']['lambd'][0]
      self.tau2 = dic['in']['lambd'][1]
    else:
      self.tau  = dic['in']['lambd']
      self.tau1 = dic['out']['lambd'][0]
      self.tau2 = dic['out']['lambd'][1]
      self.convert = True
    # some statistical info
    self.in_degree_nums  = []   # [i] : the number of nodes with in degree i
    self.out_degree_nums = []   # [i] : the number of nodes with out degree i 
    self.node_in_degree  = []   # [i] : the in degree of node i
    self.node_out_degree = []   # [i] : the out degree of node i
    self.in_degree_nodes  = []  # [i] : the nodes with in degree i
    self.out_degree_nodes = []  # [i] : the nodes with out degree i
    # generate index and nums info
    self.src_l_index = 0 
    self.src_r_index = 1 
    self.tgt_l_index = 0 
    self.tgt_r_index = 1 
    self.src_fake_cnt = 0
    self.tgt_fake_cnt = 0 
    # compress degree list, to accelerate
    self.step = 1 # TODO: config info, compress step
    self.pwl_instance = PWL(0, self.tau, self.tau1, self.tau2)
    
    self.mu_parameter = 0.4 # used to determine community belongs
    self.ncomunty = 10  # community id: 0, 1, ...
    self.comunty_nodes = []   # community: set of nodes
    # node id: start from 1
    self.node_comunty_n_indegree = [[]]  # [d1, ..., dn]
    self.node_comunty_n_outdegree = [[]] # [d1, ..., dn]
    self.node_comunty_ident = [set()]    # the communities node i belongs to
    # self.node_comunty_in_ident = [-1]  # the community node i belongs to, in degree
    # self.node_comunty_out_ident = [-1] # ditto, out degree

  def gen_node(self, one_gen):
    if one_gen['type'] == 'gaussian':
      mu = one_gen['mu']
      si = one_gen['sigma']
      gen_n = int(random.gauss(mu, si))
    elif one_gen['type'] == 'uniform':
      mi = one_gen['min']
      mx = one_gen['max']
      gen_n = random.randint(mi, mx)
    return gen_n

  def start(self):
    '''
    generate node and edges 
    '''
    try:
      rel_name = self.rel_dict['alias']
      src_name = self.rel_dict['source']
      tgt_name = self.rel_dict['target']
      if self.tgt_dic == None: # e.g. user -> user
        # src_ent_gen = GenFE(self.src_dic, self.ent_size, self.db_name)
        stage_len = len(self.src_dic['stage'])
        stage_idx = 0
        while self.src_r_index < self.src_dic['ceiling']:
          one_gen = self.src_dic['stage'][stage_idx]
          stage_idx = (stage_idx + 1) % stage_len
          gen_n = self.gen_node(one_gen)
          # src_ent_gen.start(gen_n)
          self.src_r_index += gen_n
          self.parent_conn.send((rel_name, src_name, macro.ADD_NODE, self.src_r_index))
          p1 = [self.src_l_index, self.src_r_index]
          p2 = p1[:]
          self.gen_data(p1, p2)
          # res = self.gen_data(p1, p2)
          # if res[0] == 1:
          #   self.src_r_index += (res[1] + res[2])
          #   self.src_l_index = self.src_r_index
        self.parent_conn.send((rel_name, src_name, macro.FINISH_NODE, self.src_r_index))
      else: # e.g. user -> status
        # src_ent_gen = GenFE(self.src_dic, self.ent_size, self.db_name)
        # tgt_ent_gen = GenFE(self.tgt_dic, self.ent_size, self.db_name)
        src_stg_len = len(self.src_dic['stage'])
        tgt_stg_len = len(self.tgt_dic['stage'])
        src_stg_idx = 0
        tgt_stg_idx = 0
        # TODO: when should it stop 
        while self.src_r_index < self.src_dic['ceiling'] and self.tgt_r_index < self.tgt_dic['ceiling']:
          one_src_gen = self.src_dic['stage'][src_stg_idx]
          one_tgt_gen = self.tgt_dic['stage'][tgt_stg_idx]
          src_stg_idx = (src_stg_idx + 1) % src_stg_len
          tgt_stg_idx = (src_stg_idx + 1) % tgt_stg_len
          gen_src_n = self.gen_node(one_src_gen)
          gen_tgt_n = self.gen_node(one_tgt_gen)
          # src_ent_gen.start(gen_src_n)
          # tgt_ent_gen.start(gen_tgt_n)
          self.src_r_index += gen_src_n
          self.tgt_r_index += gen_tgt_n
          # TODO: give index to parent process
          self.parent_conn.send((rel_name, src_name, macro.ADD_NODE, self.src_r_index))
          self.parent_conn.send((rel_name, tgt_name, macro.ADD_NODE, self.tgt_r_index))
          p1 = [self.src_l_index, self.src_r_index]
          p2 = [self.tgt_l_index, self.tgt_r_index]
          self.gen_data(p1, p2)
          # res = self.gen_data(p1, p2)
          # if res[0] == 1:
          #   self.src_r_index += res[1]
          #   self.src_l_index = src_r_index
          #   self.tgt_r_index += res[2]
          #   self.tgt_l_index = tgt_r_index
        self.parent_conn.send((rel_name, src_name, macro.FINISH_NODE, self.src_r_index))
        self.parent_conn.send((rel_name, tgt_name, macro.FINISH_NODE, self.tgt_r_index))
    except Exception as e:
      raise e
    finally:
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
    res = self.db_handler.query(sql)
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
      return 1
    else:
      return 0

  def gen_data(self, src_nodes, tgt_nodes):
    '''
    need to send msg to parent process
    content: (flag, extra)
            flag:  0 means do not need to add edges, while 1 means have added edges
            extra: when flag == 1, need to generate more nodes (extra)
    return : (flag, src_extra_nodes, tgt_extra_nodes)
            flag: 0, No generating edges
                  1, generate edges
            src.: generate more extra_out src nodes 
            tgt.: ditto extra_in nodes
    '''
    lens = src_nodes[1] - src_nodes[0]
    lent = tgt_nodes[1] - tgt_nodes[0]
    self.src_fake_cnt += lens
    self.tgt_fake_cnt += lent
    rel_data = []
    if self.convert:
      # compute in vector
      self.pwl_instance.set_nodes(self.tgt_fake_cnt)
      self.pwl_instance.dtmn_max_degree()
      max_in_degree = self.pwl_instance.max_d1
      cur_in_degree = pwl.get_node_count(self.tgt_fake_cnt, max_in_degree, self.tau)
      delta = max_in_degree - len(self.in_degree_nums)
      last_in_degree = self.in_degree_nums[:] + [0] * delta
      delta_in_degree = [cur_in_degree[i] - last_in_degree[i] for i in range(len(cur_in_degree))]
      (flag, extra_in, in_vector) = self.build_vector(tgt_nodes[0], tgt_nodes[1], max_in_degree, delta_in_degree, self.in_degree_nodes)
      if flag == 0:
        self.src_fake_cnt -= lens
        self.tgt_fake_cnt -= lent
        # return (0, 0, 0)
      # compute out vector
      self.pwl_instance.set_nodes(self.src_fake_cnt)
      self.pwl_instance.dtmn_max_degree()
      maxk1, maxk2, cur_out_degree = self.pwl_instance.dtmn_max_degree_2()
      delta = len(cur_out_degree) - len(self.out_degree_nums)
      last_out_degree = self.out_degree_nums[:] + [0] * delta
      delta_out_degree = [cur_out_degree[i] - last_out_degree[i] for i in range(len(cur_out_degree))]
      (flag, extra_out, out_vector) = self.build_vector(src_nodes[0], src_nodes[1], maxk2, delta_out_degree, self.out_degree_nodes)
      if flag == 0:
        self.src_fake_cnt -= lens
        self.tgt_fake_cnt -= lent
        # return (0, 0, 0)
    else:
      # compute out vector
      self.pwl_instance.set_nodes(self.src_fake_cnt)
      self.pwl_instance.dtmn_max_degree()
      max_out_degree = self.pwl_instance.max_d1
      cur_out_degree = pwl.get_node_count(self.src_fake_cnt, max_out_degree, self.tau)
      delta = max_out_degree - len(self.out_degree_nums)
      last_out_degree = self.out_degree_nums[:] + [0] * delta
      delta_out_degree = [cur_out_degree[i] - last_out_degree[i] for i in range(len(cur_out_degree))]
      (flag, extra_out, out_vector) = self.build_vector(src_nodes[0], src_nodes[1], max_out_degree, delta_out_degree, self.out_degree_nodes)
      if flag == 0:
        self.src_fake_cnt -= lens
        self.tgt_fake_cnt -= lent
        # return (0, 0, 0)
      # compute in vector
      self.pwl_instance.set_nodes(self.tgt_fake_cnt)
      self.pwl_instance.dtmn_max_degree()
      maxk1, maxk2, cur_in_degree = self.pwl_instance.dtmn_max_degree_2()
      delta = len(cur_in_degree) - len(self.in_degree_nums)
      last_in_degree = self.in_degree_nums[:] + [0] * delta
      delta_in_degree = [cur_in_degree[i] - last_in_degree[i] for i in range(len(cur_in_degree))]
      (flag, extra_in, in_vector) = self.build_vector(tgt_nodes[0], tgt_nodes[1], maxk2, delta_in_degree, self.in_degree_nodes)
      if flag == 0:
        self.src_fake_cnt -= lens
        self.tgt_fake_cnt -= lent
        # return (0, 0, 0)
    # TODO: send extra data to parent process
    self.src_r_index += extra_out
    self.src_l_index  = self.src_r_index
    self.parent_conn.send((self.rel_dict['alias'], self.rel_dict['source'], macro.ADD_NODE, self.src_r_index))
    if self.tgt_dic != None:
      self.tgt_r_index += extra_in
      self.tgt_l_index  = self.tgt_r_index
      self.parent_conn.send((self.rel_dict['alias'], self.rel_dict['target'], macro.ADD_NODE, self.tgt_r_index))
    else:
      # TODO: correct ? 
      self.src_r_index += extra_in
      self.src_l_index  = self.src_r_index
      self.parent_conn.send((self.rel_dict['alias'], self.rel_dict['source'], macro.ADD_NODE, self.src_r_index))
    # end ?
    # generate edges
    in_remain  = []
    out_remain = []
    random.shuffle(in_vector)
    random.shuffle(out_vector)
    upper = min(len(in_vector), len(out_vector))
    for i in range(upper):
      if in_vector[i] != out_vector[i]:
        # src_id = self.rel_dict['source'] + str(out_vector[i])
        # tgt_id = self.rel_dict['target'] + str(in_vector[i])
        src_id = out_vector[i]
        tgt_id = in_vector[i]
        if (src_id, tgt_id) in rel_data:
          continue
        flg = self.add_edge_info(src_id, tgt_id, out_vector[i], in_vector[i])
        if flg == 1:
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
          # src_id = self.rel_dict['source'] + str(out_remain[i])
          # tgt_id = self.rel_dict['target'] + str(in_remain[i])
          src_id = out_remain[i]
          tgt_id = in_remain[i]
          if (src_id, tgt_id) in rel_data:
            continue
          flg = self.add_edge_info(src_id, tgt_id, out_remain[i], in_remain[i])
          if flg == 1:
            rel_data.append((src_id, tgt_id))
        else:
          remain_out.append(out_remain[i])
          remain_in.append(in_remain[i])
      if len(remain_in) == 0 or len(remain_in) == threshold:
        break
      out_remain = remain_out
      in_remain  = remain_in
    # generate end
    if self.mode == 'local': # dump data locally
      # TODO: correct ?
      sql = 'insert into %s values (?, ?)' % (self.rel_dict['alias'])
      self.db_handler.insert_many(sql, rel_data)
      print('[Gen relation %s]: done' % (self.rel_dict['alias']))
    elif self.mode == 'u-level': # send info to parent process
      self.parent_conn.send((self.rel_dict['alias'], '', macro.ADD_EDGE, rel_data))
    # return (1, extra_out, extra_in)

  def homogeneous_with_uniform_comunity(self, out_vector, in_vector):
    last_old_node = self.src_r_index - 1
    new_nodes = max(max(out_vector), max(in_vector)) - last_old_node 
    tmp_comunty_size = [[_, math.ceil(new_nodes / self.ncomunty)] for _ in range(self.ncomunty)]
    node_comunty_degree = [[0 for _ in range(self.ncomunty)] for _ in range(new_nodes)] # [:][0] means the community
    node_comunty_ident = [set() for _ in range(new_nodes)]
    self.node_comunty_n_indegree.extend(node_comunty_degree)
    self.node_comunty_n_outdegree.extend(node_comunty_degree)
    # self.node_comunty_in_ident.extend(node_comunty_ident)
    # self.node_comunty_out_ident.extend(node_comunty_ident)
    self.node_comunty_ident.extend(node_comunty_ident)
    random.shuffle(out_vector)
    res_rel_data = [] # [(a, b), ...]
    while len(out_vector) > 0 and len(in_vector) > 0:
      out_node = out_vector[0]
      if len(self.node_comunty_ident[out_node]) == 0: # homeless
        tmp_index = 0
        match_old = False
        sort_tmp_comunty_size = sorted(tmp_comunty_size, key=lambda x: x[1], reverse=True)
        while tmp_index < self.ncomunty:
          recommend_cs = []
          mx_val = sort_tmp_comunty_size[tmp_index][1]
          while tmp_index < self.ncomunty and sort_tmp_comunty_size[tmp_index][1] == mx_val:
            recommend_cs.append(sort_tmp_comunty_size[tmp_index][0])
            tmp_index += 1
          match = False
          for recom_c in recommend_cs:
            candidate_in_nodes = [node for node in in_vector if node != out_node and recom_c in self.node_comunty_ident[node]]
            cand_size = len(candidate_in_nodes)
            skip = False
            if cand_size > 0:
              for in_node in candidate_in_nodes:
                if (out_node, in_node) not in res_rel_data: # find a legal edge
                  # scene: new_node -> old_node
                  res_rel_data.append((out_node, in_node))
                  self.comunty_nodes[recom_c].add(out_node)
                  self.node_comunty_ident[out_node].add(recom_c)
                  self.node_comunty_n_indegree[in_node][recom_c] += 1 
                  self.node_comunty_n_outdegree[out_node][recom_c] += 1 
                  tmp_comunty_size[recom_c][1] -= 1 
                  out_vector.remove(out_node)
                  in_vector.remove(in_node)
                  skip = True 
                  match = True 
                  match_old = True 
                  break
            if skip:
              break
          if match:
            break
        if not match_old:
          # scene: new_node -> new_node
          recom_c = sort_tmp_comunty_size[0][0]
          for in_node in in_vector:
            if in_node != out_node and (out_node, in_node) not in res_rel_data:
              res_rel_data.append((out_node, in_node))
              self.comunty_nodes[recom_c].add(out_node)
              self.comunty_nodes[recom_c].add(in_node)
              self.node_comunty_ident[out_node].add(recom_c)
              self.node_comunty_ident[in_node].add(recom_c)
              self.node_comunty_n_indegree[in_node][recom_c] += 1 
              self.node_comunty_n_outdegree[out_node][recom_c] += 1 
              tmp_comunty_size[recom_c][1] -= 2
              out_vector.remove(out_node)
              in_vector.remove(in_node)
              break
      else: # in a community, i.e. old_node
        # simple
        old_comunty = self.node_comunty_ident[out_node]
        sort_tmp_comunty_size = sorted(tmp_comunty_size, key=lambda x: x[1], reverse=True)
        mx_val = sort_tmp_comunty_size[0][1]
        recommend_cs = []
        tmp_indx = 0 
        while tmp_index < self.ncomunty:
          if sort_tmp_comunty_size[tmp_index][1] == mx_val:
            recommend_cs.append(sort_tmp_comunty_size[tmp_index][0])
          tmp_index += 1
        recm_cs_set = set(recommend_cs)
        match = False
        inter_set = old_comunty.intersection(recm_cs_set)
        if len(inter_set) > 0:
          # able to add new node
          candidate_in_nodes = [node for node in in_vector if node != out_node and len(self.node_comunty_ident[node]) == 0]
          if len(candidate_in_nodes) > 0:
            for in_node in candidate_in_nodes:
              if (out_node, in_node) not in res_rel_data:
                res_rel_data.append((out_node, in_node))
                match = True
                for recm_c in inter_set:
                  self.comunty_nodes[recm_c].add(in_node)
                  self.node_comunty_ident[in_node].add(recm_c)
                  self.node_comunty_n_indegree[in_node][recm_c] += 1 
                  self.node_comunty_n_outdegree[out_node][recm_c] += 1 
                  tmp_comunty_size[recm_c][1] -= 1 
                out_vector.remove(out_node)
                in_vector.remove(in_node)
                break
        if not match:
          for in_node in in_vector:
            if in_node != out_node and (out_node, in_node) not in res_rel_data:
              res_rel_data.append((out_node, in_node))
              in_node_comuntys = self.node_comunty_ident[in_node]
              for in_node_cmunty in in_node_comuntys:
                self.node_comunty_n_indegree[in_node][in_node_cmunty] += 1 
              for out_node_comunty in old_comunty:
                self.node_comunty_n_outdegree[out_node][out_node_comunty] += 1
              # adjust for in_node 
              in_degree = sum(self.node_comunty_n_indegree[in_node])
              for c in range(self.ncomunty):
                if self.node_comunty_n_indegree[in_node][c] * 1. / in_degree > self.mu_parameter:
                  # in_node belongs to community c
                  self.node_comunty_ident[in_node].add(c)
                  self.comunty_nodes[c].add(in_node)
              # adjust for out_node
              out_degree = sum(self.node_comunty_n_outdegree[out_node])
              for c in range(self.ncomunty):
                if self.node_comunty_n_outdegree[out_node][c] * 1. / out_degree > self.mu_parameter:
                  self.node_comunty_ident[out_node].add(c)
                  self.comunty_nodes[c].add(out_node)
              out_vector.remove(out_node)
              in_vector.remove(in_node)
              break
    return res_rel_data
  
  def heterogeneous_with_uniform_comunity(self, out_vector, in_vector):
    # yi gou network, same size community
    pass

