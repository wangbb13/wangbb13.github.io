# -*- coding: utf-8 -*- 
import sys
sys.path.append('../')
import random
from model import Store


def gen_data(ent, ent_size, start_index, n):
  rtn = [()] * n
  l = start_index
  r = l + n
  if 'tag' in ent:
    for i in range(l, r):
      _id = str(i)
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
          _tag = t_ent + str(random.randint(1, t_upp))
          for j in range(1, n):
            t_ent = ent['tag']['source'][p[j]]
            t_upp = ent_size[t_ent]
            _tag  = _tag + ' ' + t_ent + str(random.randint(1, t_upp))
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
            _tag = _tag + ' ' + t_ent + str(res)
      rtn[i-l] = (_id, _tag)
  else:
    for i in range(l, r):
      rtn[i-l] = (str(i), )
  return rtn


class GenFE(object):
  '''
  generate fixed number entity
  '''
  def __init__(self, ent, ent_size, db=None, child_conn=None):
    self.ent = ent
    self.ent_size = ent_size
    self.db  = db
    self.conn = child_conn
    self.start_idx = 1
    if db != None:
      self.db_handler = Store(self.db)
      self.db_handler.connect()

  def set_start_idx(self, n):
    self.start_idx = n

  def start(self, count):
    # count = self.ent['ceiling']
    data = gen_data(self.ent, self.ent_size, self.start_idx, count)
    self.start_idx += count
    # db first
    if self.db != None:
      name = self.ent['alias']
      if 'tag' in self.ent:
        sql = 'insert into %s values (?, ?)' % (name)
      else:
        sql = 'insert into %s values (?)' % (name)
      self.db_handler.insert_many(sql, data)
    # conn second
    else:
      assert self.child_conn != None
      self.child_conn.send(data)

