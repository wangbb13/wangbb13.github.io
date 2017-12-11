# -*- coding: utf-8 -*- 

import os
import sys
from gen import legal

sql_tabl = 'create table %s ( \n%s \n); \n\n'
sql_pkey = '  primary key (%s)'
sql_fkey = '  foreign key (%s) references %s (%s)'
sql_comm = '  %s      varchar(%d)'
prmy_sql_comm = '  %s      varchar(%d) primary key'
sql_time = '  %s      timestamp'

ent_set = set()
rel_set = set()
key_size = {}

def pre_manipulate(gdb):
  for ent in gdb['entity']:
    ent_set.add(ent['alias'])
    size = 12
    upper = ent['ceiling']
    if upper != float('inf'):
      size = len(str(upper))
    key_size[ent['alias']] = size + len(ent['alias'])
  for rel in gdb['relation']:
    rel_set.add(rel['alias'])


def count_size(gdb):
  res = {}
  for ent in gdb['entity']:
    res[ent['alias']] = ent['ceiling']
  return res


def ent_sql(ent_dict):
  tbl = ent_dict['alias']
  content = prmy_sql_comm % (tbl + '_id', key_size[tbl])
  if 'tag' in ent_dict:
    if ent_dict['tag']['mode'] == 'respective':
      fac = int(ent_dict['tag']['count'][-1])
      cnt = len(ent_dict['tag']['source']) * fac
      for tg in ent_dict['tag']['source']:
        cnt += key_size[tg] * fac
      content =  content + ', \n' + sql_comm % ('tags', cnt)
    else:
      fac = int(ent_dict['tag']['count'][-1])
      cnt = fac * (max([key_size[x] for x in ent_dict['tag']['source']]) + 1)
      content = content + ', \n' + sql_comm % ('tags', cnt)
  return sql_tabl % (tbl, content)


def rel_sql(rel_dict):
  tbl = rel_dict['alias']
  src = rel_dict['source']
  tgt = rel_dict['target']
  content = sql_comm % ('src_id', key_size[src]) + ', \n' \
          + sql_comm % ('tgt_id', key_size[tgt]) + ', \n' \
          + sql_pkey % ('src_id, tgt_id') + ', \n' \
          + sql_fkey % ('src_id', src, src + '_id') + ', \n' \
          + sql_fkey % ('tgt_id', tgt, tgt + '_id')
  return sql_tabl % (tbl, content)


def tbl_sql(gdb):
  legal(gdb)
  pre_manipulate(gdb)
  ans = ''
  for ent in gdb['entity']:
    ans = ans + ent_sql(ent)
  for rel in gdb['relation']:
    ans = ans + rel_sql(rel)
  return ans


def delete_sql(gdb):
  res = ''
  for ent in gdb['entity']:
    res = res + 'delete from %s \n' % (ent['alias'])
  for rel in gdb['relation']:
    res = res + 'delete from %s \n' % (rel['alias'])
  return res


def test():
  if len(sys.argv) != 2:
    print('Usage: python crt_ddl.py filename')
    return
  filename = sys.argv[1]
  from test import test_scheme
  ddl = tbl_sql(test_scheme)
  with open(filename, 'w') as f:
    f.write(ddl)
  print('done')


if __name__ == '__main__':
  test()
