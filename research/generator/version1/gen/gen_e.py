# -*- coding: utf-8 -*- 
import sys
sys.path.append('../')
import random
from model import Store
from tools import random_str
from datetime import datetime, timedelta

separator = ','

def gen_data(ent, ent_size, start_index, n):
  rtn = [()] * n
  l = start_index
  r = l + n
  for i in range(l, r):
    recd = [i]
    if 'tag' in ent:
      _tag = ''
      if ent['tag']['mode'] == 'random':
        n = random.randint(ent['tag']['count'][0], ent['tag']['count'][1])
        b = len(ent['tag']['source']) - 1
        t_ent = ent['tag']['source'][random.randint(0, b)]
        t_upp = ent_size[t_ent]
        _tag = t_ent + str(random.randint(1, t_upp))
        for j in range(n-1):
          t_ent = ent['tag']['source'][random.randint(0, b)]
          t_upp = ent_size[t_ent]
          _tag  = _tag + separator + t_ent + str(random.randint(1, t_upp))
      elif ent['tag']['mode'] == 'exclusive':
        b = len(ent['tag']['source'])
        l = min(b, min(ent['tag']['count']))
        r = min(b, max(ent['tag']['count']))
        n = random.randint(l, r)
        p = [x for x in range(b)]
        if n > 0:
          t_ent = ent['tag']['source'][p[0]]
          t_upp = ent_size[t_ent]
          _tag = t_ent + str(random.randint(1, t_upp))
          for j in range(1, n):
            t_ent = ent['tag']['source'][p[j]]
            t_upp = ent_size[t_ent]
            _tag  = _tag + separator + t_ent + str(random.randint(1, t_upp))
      else: # respective
        for t_ent in ent['tag']['source']:
          t_upp = ent_size[t_ent]
          l = min(t_upp, min(ent['tag']['count']))
          r = min(t_upp, max(ent['tag']['count']))
          n = random.randint(l, r)
          tp_set = set()
          for _ in range(n):
            while True:
              res = random.randint(1, t_upp)
              if res not in tp_set:
                break
            tp_set.add(res)
            _tag = _tag + separator + t_ent + str(res)
      recd.append(_tag)
    if 'attr' in ent:
      # TODO: how to generate reasonable random str ? 
      # TODO: how to genreate reasonable timestamp ? 
      # TODO: other types ? 
      for one_attr in ent['attr']:
        if 'range' in one_attr['value']:
          idx = random.randint(0, len(one_attr['value']['range']))
          recd.append(one_attr['value']['range'][idx])
        else:
          if one_attr['value']['type'] == str:
            str_len = random.randint(1, 100)
            recd.append(random_str.random_str(str_len))
          elif one_attr['value']['type'] == datetime:
            start_time = datetime.now() - timedelta(1, 0, 0)
            seconds = 24 * 60 * 60
            recd.append(random_str.random_time(start_time, seconds))
    rtn[i-l] = tuple(recd)
  return rtn


class GenFE(object):
  '''
  generate fixed number entity
  '''
  def __init__(self, ent, ent_size, db):
    self.ent = ent
    self.ent_size = ent_size
    self.db  = db
    self.start_idx = 0 
    self.db_handler = Store(self.db)
    self.db_handler.connect()

  def set_start_idx(self, n):
    self.start_idx = n

  def start(self, max_id):
    # max_id: the max id should be generated
    count = max_id - start_idx + 1
    if count < 1:
      return 
    data = gen_data(self.ent, self.ent_size, self.start_idx, count)
    self.start_idx += count
    # dump data to db
    name = self.ent['alias']
    sql = 'insert into %s values (?' % (name)
    if 'tag' in self.ent:
      sql = sql + ', ?'
    if 'attr' in self.ent:
      sql = sql + ', ?' * len(self.ent['attr'])
    sql = sql + ')'
    try:
      self.db_handler.insert_many(sql, data)
    except Exception as e:
      raise e
    print('[Node Generation]: Name %s, Max ID %s' % (name, max_id))

