# -*- coding: utf-8 -*-
import os
import sys
import argparse
import random
import sqlite3
from datetime import datetime
import time, threading
import math

import models
import config
import distribution
import data


def generate_fixed_entity():
  entities = config.db['entity']
  conn, cursor = models.connect_db()
  for ent in entities:
    if ent['amount'] == 'fixed':
      name = ent['alias']
      table_list = [name+str(i+1) for i in range(ent['range'][0])]
      try:
        cursor.execute('insert into %s values (?)' % (name), table_list)
        conn.commit()
      except Exception as e:
        models.close_db(conn, cursor)
        raise e
  models.close_db(conn, cursor)


def generate_fixed_entity_relation():
  entities = config.db['entity']
  conn, cursor = models.connect_db()
  for ent in entities:
    e_tag = ent['tag']
    if e_tag['source'] == 'from-db' and e_tag['range'] == [1,1] and len(e_tag['content']):
      name = ent['alias']
      ref  = e_tag['content'][0]
      table = name + '_' + ref
      cursor.execute('select * from %s' % (name))
      name_list = [x[0] for x in cursor.fetchall()]
      cursor.execute('select * from %s' % (ref))
      ref_list = [x[0] for x in cursor.fetchall()]
      ref_end = len(ref_list) - 1
      name_ref_list = [(name_list[i], ref_list[random.randint(0,ref_end)]) \
      for i in range(len(name_list))]
      try:
        cursor.execute('insert into %s values (?,?)' % (table), table_list)
        conn.commit()
      except Exception as e:
        models.close_db(conn, cursor)
        raise e

  models.close_db(conn, cursor)


# input: dic, dict of an entity
def generate_dynamic_entity(dic):
  table_name = dic['alias']
  distr_list = dic['stage']
  relations = config.db['relation']
  conn, cursor = models.connect_db()
  cursor.execute('select count(*) from %s' % (table_name))
  start_index = cursor.fetchall()[0][0] + 1
  counter = 0
  for rela in relations:
    if rela['source'] == table_name and rela['target'] == table_name:
      break
  # for test run time
  time_start = time.time()
  fake_size = start_index - 1
  gen_start_i = start_index
  gen_rela_num = 0
  fg = 0
  for x in range(dic['count']):
    try:
      distr = distr_list[counter]
      gen_num = 0
      if distr['type'] == 'gaussian':
        gen_num = round(random.gauss(distr['mu'], distr['sigma']))
      else:
        gen_num = round(random.randint(distr['min'], distr['max']))
      for i in range(start_index, start_index+gen_num):
        item_id = table_name + str(i)
        item_tag = ''
        # TODO: generate tags
        data.user_data.add((item_id, item_tag))
      # TODO: just for follow, hard code
      #       should find relations including table_name
      fake_size += gen_num
      gen_rela_num += gen_num
      change_list = [gen_start_i, gen_rela_num, fake_size]
      # print('******************************************************')
      # print('in_degree_node', data.degree_node)
      # print('in info', [len(x) for x in data.degree_node])
      # print('out_degree_noe', data.out_degree_node)
      # print('out info', [len(x) for x in data.out_degree_node])
      # print('======================================================')
      fg = generate_dynamic_relation(change_list, table_name, rela)
      # print('======================================================')
      time.sleep(config.delay_time)
      counter = (counter + 1) % (len(distr_list))
      start_index = len(data.user_data) + 1
      if fg == 0:
        gen_start_i = start_index
        gen_rela_num = 0
      # print(start_index)
    except Exception as e:
      # models.close_db(conn, cursor)
      raise e
  while fg == 1:
    try:
      distr = distr_list[counter]
      gen_num = 0
      if distr['type'] == 'gaussian':
        gen_num = round(random.gauss(distr['mu'], distr['sigma']))
      else:
        gen_num = round(random.randint(distr['min'], distr['max']))
      for i in range(start_index, start_index+gen_num):
        item_id = table_name + str(i)
        item_tag = ''
        # TODO: generate tags
        data.user_data.add((item_id, item_tag))
      # TODO: just for follow, hard code
      #       should find relations including table_name
      fake_size += gen_num
      gen_rela_num += gen_num
      change_list = [gen_start_i, gen_rela_num, fake_size]
      # print('======================================================')
      fg = generate_dynamic_relation(change_list, table_name, rela)
      # print('======================================================')
      time.sleep(config.delay_time)
      counter = (counter + 1) % (len(distr_list))
      start_index = len(data.user_data) + 1
      if fg == 0:
        gen_start_i = start_index
        gen_rela_num = 0
    except Exception as e:
      raise e
  with open('graph_size.py', 'w') as f:
    f.write(str(fake_size))
  print('elapsed %f sec. nodes: %d' % (time.time() - time_start, fake_size))
  try:
    cursor.executemany('insert into %s values (?,?)' % table_name, list(data.user_data))
    cursor.executemany("insert into %s values (?,?,?)" % rela['alias'], list(data.follow_data))
    conn.commit()
    # print([len(x) for x in data.degree_node])
  except Exception as e:
    models.close_db(conn, cursor)
    raise e


def compute_in_vector(last_in_degree, change_list, in_lambd, table_name):
  # in  degree
  max_in_degree = distribution.pwl_determine_max_degree(change_list[2], in_lambd)
  x_list = [i+1 for i in range(max_in_degree)]
  cur_in_degree = distribution.pwl_node_count(change_list[2], x_list, in_lambd)
  delta = max_in_degree - len(last_in_degree)
  last_in_degree = last_in_degree + [0] * delta
  delta_in_degree = list(map(lambda t: t[0] - t[1], list(zip(cur_in_degree, last_in_degree))))
  # solve negative number in delta_out_degree
  minus = 0
  for i in range(len(delta_in_degree)):
    if delta_in_degree[i] < 0:
      delta_in_degree[i] = 0
    if delta_in_degree[i] == 0:
      minus += 1
  if minus > (len(delta_in_degree) / 3):
    return ([], 1)
  # end solve
  # print('civ: delta_in_degree', delta_in_degree)
  # print('civ: total degree', distribution.total_degree(delta_in_degree))
  # new node id
  end_i = change_list[0]+change_list[1]
  new = [i for i in range(change_list[0], end_i)]
  # print('civ: new ', new)
  # explain: new_i, first new_index take from new data
  #          compress_in_degree, compress delta_in_degree according to config.degree_precise
  compress_in_degree = []
  step = config.degree_precise
  ii = 0
  for i in range(int(math.floor(max_in_degree / step))):
    s = 0
    for j in range(i*step, i*step + step):
      s += delta_in_degree[j]
    compress_in_degree.append(s)
    ii = i
  s = 0
  for j in range(ii*step+step, max_in_degree):
    s += delta_in_degree[j]
  if s != 0:
    compress_in_degree.append(s)
  # print('civ: compress_in_degree', compress_in_degree)
  random.shuffle(new)
  # compute in vector
  in_vector = []
  if len(data.degree_node) == 0:
    # print('civ: first add data')
    index = 0
    repeat = 1
    for num in delta_in_degree:
      in_vector += [x for x in new[index:index+num] for j in range(repeat)]
      index += num
      repeat += 1
    # print('civ: first, in_vector', in_vector)
  else:
    len_comp  = len(compress_in_degree)
    len_in    = len(data.degree_node)
    delta_len = len_comp - len_in
    # very very important, modify compress_in_degree
    if delta_len <= 0:
      for i in range(len_comp-2, -1, -1):
        compress_in_degree[i] += compress_in_degree[i+1]
    else:
      if delta_len >= len_in:
        for i in range(delta_len, len_comp):
          compress_in_degree[i - delta_len] += compress_in_degree[i]
      else:
        for i in range(len_comp - delta_len, len_comp):
          for j in range(i-delta_len, -1, (-delta_len)):
            compress_in_degree[j] += compress_in_degree[j+delta_len]
    # end very important
    # print('civ: modify compress ', compress_in_degree)
    if delta_len <= 0:
      # add fake nodes
      more = max(0, compress_in_degree[0] - len(new))
      # print('cov: need add %d fake nodes' % more)
      new += [i for i in range(end_i, end_i + more)]
      for i in range(end_i, end_i + more):
        en_id = table_name + str(i)
        en_tag = ''
        data.user_data.add((en_id, en_tag))
      end_i += more
      # print('cov: new', new)
      # end add fake nodes
      # print('civ: not extent', len(compress_in_degree), len(data.degree_node))
      new_i = 0
      in_vector += new[new_i:new_i + compress_in_degree[0]] * step
      new_i += compress_in_degree[0]
      # print('civ: add new, len(in)', len(in_vector))
      # print('civ: in_vector, add new data', in_vector)
      j = 0
      for i in range(1, len(compress_in_degree)):
        comp_size = compress_in_degree[i] - len(data.degree_node[j])
        in_vector += data.degree_node[j][:compress_in_degree[i]] * step
        # print('civ: add orig, len(in)', len(in_vector))
        # print('civ: in_vector, add org data', data.degree_node[j][:compress_in_degree[i]] * step)
        if comp_size > 0:
          # add new fake node 
          more = max(comp_size - (end_i - new_i), 0)
          # print('cov: need add %d fake nodes' % more)
          new += [i for i in range(end_i, end_i + more)]
          for i in range(end_i, end_i + more):
            en_id = table_name + str(i)
            en_tag = ''
            data.user_data.add((en_id, en_tag))
          end_i += more
          # print('cov: new', new)
          # end add fake nodes
          in_vector += new[new_i:new_i+comp_size] * (step * (i+1))
          # print('civ: in_vector, add new data', new[new_i:new_i+comp_size] * (step * (i+1)))
          # print('civ: add new, len(in)', len(in_vector))
          new_i += comp_size
        j += 1
    else:
      # add fake nodes
      more = max(0, sum(compress_in_degree[:delta_len]) - len(new))
      # print('cov: need add %d fake nodes' % more)
      new += [i for i in range(end_i, end_i + more)]
      for i in range(end_i, end_i + more):
        en_id = table_name + str(i)
        en_tag = ''
        data.user_data.add((en_id, en_tag))
      end_i += more
      # print('cov: new', new)
      # end add fake nodes
      # print('civ: extent', len(compress_in_degree), len(data.degree_node))
      new_i = 0
      for i in range(delta_len):
        in_vector += new[new_i:new_i + compress_in_degree[i]] * (step * (i+1))
        new_i += compress_in_degree[i]
      # print('civ: add new, len(in)', len(in_vector))
      # print('civ: in_vector, add new data', in_vector)
      j = 0
      for i in range(delta_len, len(compress_in_degree)):
        comp_size = compress_in_degree[i] - len(data.degree_node[j])
        in_vector += data.degree_node[j][:compress_in_degree[i]] * (step * delta_len)
        # print('civ: add orig, len(in)', len(in_vector))
        # print('civ: in_vector, add org data', data.degree_node[j][:compress_in_degree[i]] * (step * delta_len))
        if comp_size > 0:
          # add new fake node 
          more = max(comp_size - (end_i - new_i), 0)
          # print('cov: need add %d fake nodes' % more)
          new += [i for i in range(end_i, end_i + more)]
          for i in range(end_i, end_i + more):
            en_id = table_name + str(i)
            en_tag = ''
            data.user_data.add((en_id, en_tag))
          end_i += more
          # print('cov: new', new)
          # end add fake nodes
          in_vector += new[new_i:new_i+comp_size] * (step * (i+1))
          # print('civ: in_vector, add new data', new[new_i:new_i+comp_size] * (step * (i+1)))
          # print('civ: add new, len(in)', len(in_vector))
          new_i += comp_size
        j += 1

  return (in_vector, 0)
  # return (in_vector, cur_in_degree)


def compute_out_vector(last_out_degree, change_list, t1, ol1, ol2, table_name):
  gen_len = change_list[1]
  # compute cur_out_degree
  cur_out_degree = []
  maxk1, maxk2, stage2_degree = distribution.pwl_deter_max_degree_two_lambd(change_list[2], t1, ol1, ol2)
  x_list = [i+1 for i in range(maxk1)]
  cur_out_degree += distribution.pwl_node_count(change_list[2], x_list, ol1)
  cur_out_degree += stage2_degree
  delta = len(cur_out_degree) - len(last_out_degree)
  last_out_degree = last_out_degree + [0] * delta
  delta_out_degree = list(map(lambda t: t[0] - t[1], list(zip(cur_out_degree, last_out_degree))))
  # solve negative number in delta_out_degree
  minus = 0
  for i in range(len(delta_out_degree)):
    if delta_out_degree[i] < 0:
      delta_out_degree[i] = 0
    if delta_out_degree[i] == 0:
      minus += 1
  if minus > (len(delta_out_degree) / 2):
    return ([], 1)
  # end solve
  # print('cov: delta_out_degree', delta_out_degree)
  # print('cov: total degree', distribution.total_degree(delta_out_degree))
  # new node id
  end_i = change_list[0]+change_list[1]
  new = [i for i in range(change_list[0], end_i)]
  # print('cov: new', new)
  # explain: new_i, first new_index take from new data
  #          compress_out_degree, compress delta_out_degree according to config.degree_precise
  compress_out_degree = []
  step = config.degree_precise
  ii = 0
  for i in range(int(math.floor(maxk2 / step))):
    s = 0
    for j in range(i*step, i*step + step):
      s += delta_out_degree[j]
    compress_out_degree.append(s)
    ii = i
  s = 0
  for j in range(ii*step+step, maxk2):
    s += delta_out_degree[j]
  if s != 0:
    compress_out_degree.append(s)
  # print('cov: compress_out_degree', compress_out_degree)
  random.shuffle(new)
  # compute out_vector
  out_vector = []
  if len(data.out_degree_node) == 0:
    # print('cov: first add data')
    cur_len = sum(delta_out_degree)
    more = max(0, cur_len - gen_len)
    # print('cov: need add fake %d nodes' % (more))
    # add user to user_data
    new += [i for i in range(end_i, end_i + more)]
    # print('cov: new', new)
    for i in range(end_i, end_i + more):
      en_id = table_name + str(i)
      en_tag = ''
      data.user_data.add((en_id, en_tag))
    # end add fake nodes
    index = 0
    repeat = 1
    for num in delta_out_degree:
      out_vector += [x for x in new[index:index+num] for j in range(repeat)]
      index += num
      repeat += 1
    # print('cov: out_vector', out_vector)
  else:
    len_comp  = len(compress_out_degree)
    len_out   = len(data.out_degree_node)
    delta_len = len_comp - len_out
    # very very important, modify compress_in_degree
    if delta_len <= 0:
      for i in range(len_comp-2, -1, -1):
        compress_out_degree[i] += compress_out_degree[i+1]
    else:
      if delta_len >= len_out:
        for i in range(delta_len, len_comp):
          compress_out_degree[i - delta_len] += compress_out_degree[i]
      else:
        for i in range(len_comp - delta_len, len_comp):
          for j in range(i-delta_len, -1, (-delta_len)):
            compress_out_degree[j] += compress_out_degree[j+delta_len]
    # end very important
    # print('cov: modify compress', compress_out_degree)
    if delta_len <= 0:
      # print('cov: not extent', len(compress_out_degree), len(data.out_degree_node))
      # add fake nodes
      more = max(0, compress_out_degree[0] - len(new))
      # print('cov: need add %d fake nodes' % more)
      new += [i for i in range(end_i, end_i + more)]
      for i in range(end_i, end_i + more):
        en_id = table_name + str(i)
        en_tag = ''
        data.user_data.add((en_id, en_tag))
      end_i += more
      # print('cov: new', new)
      # end add fake nodes
      new_i = 0
      out_vector += new[new_i:new_i + compress_out_degree[0]] * step
      new_i += compress_out_degree[0]
      # print('cov: add new data', out_vector)
      j = 0
      for i in range(1, len(compress_out_degree)):
        comp_size = compress_out_degree[i] - len(data.out_degree_node[j])
        out_vector += data.out_degree_node[j][:compress_out_degree[i]] * step
        # print('cov: add org data', data.out_degree_node[j][:compress_out_degree[i]] * step)
        if comp_size > 0:
          # add new fake node 
          more = max(comp_size - (end_i - new_i), 0)
          # print('cov: need add %d fake nodes' % more)
          new += [i for i in range(end_i, end_i + more)]
          for i in range(end_i, end_i + more):
            en_id = table_name + str(i)
            en_tag = ''
            data.user_data.add((en_id, en_tag))
          end_i += more
          # print('cov: new', new)
          # end add fake nodes
          out_vector += new[new_i:new_i+comp_size] * (step * (i+1))
          # print('cov: add new data', new[new_i:new_i+comp_size] * (step * (i+1)))
          # print('cov: new_i, comp_size, new_len', new_i, comp_size, len(new))
          new_i += comp_size
        j += 1
    else:
      # print('cov: extent', len(compress_out_degree), len(data.out_degree_node))
      # add fake nodes
      more = max(0, sum(compress_out_degree[:delta_len]) - len(new))
      # print('cov: need add %d fake nodes' % more)
      new += [i for i in range(end_i, end_i + more)]
      for i in range(end_i, end_i + more):
        en_id = table_name + str(i)
        en_tag = ''
        data.user_data.add((en_id, en_tag))
      end_i += more
      # print('cov: new', new)
      # end add fake nodes
      new_i = 0
      for i in range(delta_len):
        out_vector += new[new_i:new_i + compress_out_degree[i]] * (step * (i+1))
        new_i += compress_out_degree[i]
      j = 0
      # print('cov: add new data', out_vector)
      for i in range(delta_len, len(compress_out_degree)):
        comp_size = compress_out_degree[i] - len(data.out_degree_node[j])
        out_vector += data.out_degree_node[j][:compress_out_degree[i]] * (step * delta_len)
        # print('cov: add org data', data.out_degree_node[j][:compress_out_degree[i]] * (step * delta_len))
        if comp_size > 0:
          # add new fake node 
          more = max(comp_size - (end_i - new_i), 0)
          # print('cov: need add %d fake nodes' % more)
          new += [i for i in range(end_i, end_i + more)]
          for i in range(end_i, end_i + more):
            en_id = table_name + str(i)
            en_tag = ''
            data.user_data.add((en_id, en_tag))
          end_i += more
          # print('cov: new', new)
          # end add fake nodes
          out_vector += new[new_i:new_i+comp_size] * (step * (i+1))
          # print('cov: add new data', new[new_i:new_i+comp_size] * (step * (i+1)))
          new_i += comp_size
        j += 1

  return (out_vector, 0)
  # return (out_vector, cur_out_degree)


def add_edge_info(src_id, tag_id, out_i, in_i, tstamp):
  if (src_id, tag_id, tstamp) not in data.follow_data:
    for ss in range(len(data.node_out_degree), out_i+1):
      data.node_out_degree.append(0)
    data.node_out_degree[out_i] += 1
    degreei = data.node_out_degree[out_i]
    ind = int(degreei / config.degree_precise)
    ind_ = int((degreei-1) / config.degree_precise)
    if config.degree_precise == 1:
      ind -= 1
      ind_ -= 1
    for ss in range(len(data.out_degree_node), ind+1):
      data.out_degree_node.append([])
    if degreei == 1:
      data.out_degree_node[0].append(out_i)
    elif degreei % config.degree_precise == 0:
      try:
        data.out_degree_node[ind_].remove(out_i)
      except Exception as e:
        pass
      data.out_degree_node[ind].append(out_i)
    
    for ss in range(len(data.node_in_degree), in_i+1):
      data.node_in_degree.append(0)
    data.node_in_degree[in_i] += 1
    degreei = data.node_in_degree[in_i]
    ind = int(degreei / config.degree_precise)
    ind_ = int((degreei-1) / config.degree_precise)
    if config.degree_precise == 1:
      ind -= 1
      ind_ -= 1
    for ss in range(len(data.degree_node), ind+1):
      data.degree_node.append([])
    if degreei == 1:
      data.degree_node[0].append(in_i)
    elif degreei % config.degree_precise == 0:
      try:
        data.degree_node[ind_].remove(in_i)
      except Exception as e:
        pass
      data.degree_node[ind].append(in_i)


# input: change_list [a, b], data generated lately, old data: a, new data: b
#        table_nmae, data of which table
#        relation_dic, related relation
def generate_dynamic_relation(change_list, table_name, relation_dic):
  last_in_degree = []
  last_out_degree = []
  gen_len = change_list[1]
  in_lambd  = relation_dic['in_distr']['lambd']
  out_lambd1 = relation_dic['out_distr']['lambd'][0]
  out_lambd2 = relation_dic['out_distr']['lambd'][1]
  conn, cursor = models.connect_db()
  # get info from file
  file = os.path.join('./profile', table_name+'.info')
  if os.path.exists(file):
    with open(file, 'r') as f:
      last_in_degree  = list(map(lambda x: int(x), f.readline().strip().split()))
      last_out_degree = list(map(lambda x: int(x), f.readline().strip().split()))
  # in vector
  in_vector, flag1 = compute_in_vector(last_in_degree, change_list, in_lambd, table_name)
  if flag1 == 1:
    return 1
  # out degree
  out_vector, flag2 = compute_out_vector(last_out_degree, change_list, in_lambd, out_lambd1, out_lambd2, table_name)
  if flag2 == 1:
    return 1
  # in and out vector end.
  # record info to file
  # with open(file, 'w') as f:
  #   string = ' '.join([str(i) for i in cur_in_degree]) + '\n'
  #   f.write(string)
  #   string = ' '.join([str(i) for i in cur_out_degree]) + '\n'
  #   f.write(string)
  # end record
  # link two vectors, out -> in
  out_remain = []
  in_remain  = []
  random.shuffle(out_vector)
  random.shuffle(in_vector)
  # print('gdr: two vector lens (out, in)', len(out_vector), len(in_vector))
  try:
    for i in range(min(len(in_vector), len(out_vector))):
      if in_vector[i] != out_vector[i]:
        src_id = table_name + str(out_vector[i])
        tag_id = table_name + str(in_vector[i])
        tstamp = ''
        add_edge_info(src_id, tag_id, out_vector[i], in_vector[i], tstamp)
        data.follow_data.add((src_id, tag_id, tstamp))
      else:
        out_remain.append(out_vector[i])
        in_remain.append(in_vector[i])
    
    while True:
      threshold = len(out_remain)
      remain_out = []
      remain_in = []
      random.shuffle(out_remain)
      random.shuffle(in_remain)
      for i in range(len(out_remain)):
        if out_remain[i] != in_remain[i]:
          src_id = table_name + str(out_remain[i])
          tag_id = table_name + str(in_remain[i])
          tstamp = ''
          add_edge_info(src_id, tag_id, out_vector[i], in_vector[i], tstamp)
          data.follow_data.add((src_id, tag_id, tstamp))
        else:
          remain_out.append(out_remain[i])
          remain_in.append(in_remain[i])
      if len(remain_in) == 0 or len(remain_in) == threshold:
        break
      out_remain = remain_out
      in_remain  = remain_in
      
    # print('gdr: remain nodes(out, in)', remain_out, remain_in)
    # record info to file
    with open(file, 'w') as f:
      string = ' '.join([str(i) for i in [len(x) for x in data.degree_node]]) + '\n'
      f.write(string)
      string = ' '.join([str(i) for i in [len(x) for x in data.out_degree_node]]) + '\n'
      f.write(string)
    # end record
    return 0
  except Exception as e:
    raise e


'''
def generate_dynamic_entities():
  relations = config.db['entity']
  thread_list = [threading.Thread(target=generate_dynamic_entity, args=(dic,)) \
  for dic in relations if dic['amount'] == 'dynamic']
  for thread in thread_list:
    thread.start()
'''
