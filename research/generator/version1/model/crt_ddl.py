# -*- coding: utf-8 -*- 

import os
import sys
sys.path.append('../')
from gen import parser

sql_tabl = 'create table %s ( \n%s); \n\n'
sql_pkey = '  primary key (%s), \n'
sql_fkey = '  foreign key (%s) references %s (%s), \n'
sql_comm = '  %s      varchar(%d), \n'
sql_time = '  %s      timestamp, \n'

ent_set = set()
rel_set = set()
key_size = {}

def pre_manipulate(gdb):
  parser.legal(gdb)
  for ent in gdb['entity']:
    ent_set.add(ent['alias'])
    size = 12
    upper = ent['ceiling']
    if upper != float('inf'):
      size = len(str(upper))
    key_size[ent['alias']] = size + len(ent['alias'])
  for rel in gdb['relation']:
    rel_set.add(rel['alias'])


def ent_sql(ent_dict):
  tbl = ent_dict['alias']
  content = sql_comm % (tbl + '_id', key_size[tbl])
  if 'tag' in ent_dict:
    if ent_dict['tag']['mode'] == 'respective':
      fac = int(ent_dict['tag']['count'][-1])
      cnt = len(ent_dict['tag']['source']) * fac
      for tg in ent_dict['tag']['source']:
        cnt += key_size[tg] * fac
      content = content + sql_comm % ('tags', cnt)
    else:
      fac = int(ent_dict['tag']['count'][-1])
      cnt = fac * (max([key_size[x] for x in ent_dict['tag']['source']]) + 1)
      content = content + sql_comm % ('tags', cnt)
  content = content + sql_pkey % (tbl + '_id')
  return sql_tabl % (tbl, content)


def rel_sql(rel_dict):
  tbl = rel_dict['alias']
  src = rel_dict['source']
  tgt = rel_dict['target']
  content = sql_comm % ('src_id', key_size[src]) \
          + sql_comm % ('tgt_id', key_size[tgt]) \
          + sql_pkey % ('src_id, tgt_id') \
          + sql_fkey % ('src_id', src, src + '_id') \
          + sql_fkey % ('tgt_id', tgt, tgt + '_id')
  return sql_tabl % (tbl, content)


def tbl_sql(gdb):
  pre_manipulate(gdb)
  ans = ''
  for ent in gdb['entity']:
    ans = ans + ent_sql(ent)
  for rel in gdb['relation']:
    ans = ans + rel_sql(rel)
  return ans


def test():
  sys.path.append('../test')
  import config
  ddl = tbl_sql(config.gdb)
  print(ddl)


if __name__ == '__main__':
  test()
