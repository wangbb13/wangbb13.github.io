# -*- coding: utf-8 -*-
import os
import sys
sys.path.append('../')

from multiprocessing import Pipe, Value, Array, Process

from model import tbl_sql, delete_sql, count_size, Store
from gen import GenDDR, GenFE
from mytest import config 
from tools import macro


class TestMain(object):
  '''
  test full process
  '''
  def __init__(self, scheme):
    self.scheme = scheme
    self.db_name = scheme['alias'] + '.db'
    self.db_handler = Store(self.db_name)
    self.db_handler.connect()

  def db_exist(self):
    return os.path.exists(self.db_name)

  def create_db(self):
    try:
      crt_db_sql = tbl_sql(self.scheme)
      with open('ddl.sql', 'w') as f:
        f.write(crt_db_sql)
      self.db_handler.execute_script(crt_db_sql)
      print('[Create DB %s]: done' % (self.db_name))
    except Exception as e:
      raise e

  def clear_db(self):
    try:
      dlt_sql = delete_sql(self.scheme)
      self.db_handler.execute_script(dlt_sql)
      print('[Clear DB %s]: done' % (self.db_name))
    except Exception as e:
      raise e

  def main_proc(self, mode='local'):
    # TODO: 
    ent_size = count_size(self.scheme)
    s_conn, c_conn = Pipe()
    ents = self.scheme['entity']
    rels = self.scheme['relation']
    ent_idx = {}
    ent_set = set()
    rel_set = set()
    rel_idx = {}
    idx = 0
    for one_ent in ents:
      ent_idx[one_ent['alias']] = idx
      ent_set.add(one_ent['alias'])
      idx += 1
    idx = 0
    for one_rel in rels:
      rel_set.add(one_rel['alias'])
      rel_idx[one_rel['alias']] = idx 
      idx += 1
    # generate procedure
    ent_gen_dict = {}
    ent_gen_list = []
    rel_gen_dict = {}
    rel_gen_list = []
    for one_ent in ents:
      ent_gen_dict[one_ent['alias']] = GenFE(one_ent, ent_size, self.db_name)
      ent_gen_list.append(ent_gen_dict[one_ent['alias']])
    for one_rel in rels:
      sc_name = one_rel['source']
      tg_name = one_rel['target']
      if sc_name == tg_name:
        rel_ins = GenDDR(self.db_name, one_rel, c_conn, ents[ent_idx[sc_name]], ent_size, mode=mode)
      else:
        rel_ins = GenDDR(self.db_name, one_rel, c_conn, ents[ent_idx[sc_name]], ent_size, ents[ent_idx[tg_name]], mode=mode)
      rel_gen_dict[one_rel['alias']] = rel_ins
      rel_gen_list.append(rel_ins)
    # build sub process and start them
    rel_proc_dict = {}
    for rel_name, gen_ins in rel_gen_dict.items():
      rel_proc_dict[rel_name] = Process(target=gen_ins.start)
      rel_proc_dict[rel_name].start()
    # core processing
    flag_rel_p = [True] * len(rel_idx)
    flag_ent_p = [True] * len(ent_idx)
    try:
      while sum(flag_rel_p) > 0:
        '''
        message format: (rel_name, ent_name or '', sign, max_index(for node) or rel_data(for relation) or '')
        '''
        res = s_conn.recv()
        print('[Recv Msg]: from %s sub process' % (res[0]))
        assert res[0] in rel_set and res[1] in ent_set
        if res[2] == macro.ADD_NODE or res[2] == macro.FINISH_NODE:
          _ent_ = res[1]
          ent_gen_dict[_ent_].start(res[3])
          if res[2] == macro.FINISH_NODE:
            flag_ent_p[ent_idx[res[1]]] = False
            print('[Node Generation]: Name %s, End' % (res[1]))
        elif res[2] == macro.ADD_EDGE:
          ist_sql = 'insert into %s values (?, ?)' % (res[0])
          self.db_handler.insert_many(ist_sql, res[3])
          print('[Edge Generation]: Name %s, Amount %s' % (res[0], len(res[3])))
        elif res[2] == macro.FINISH_EDGE:
          flag_rel_p[rel_idx[res[0]]] = False
          print('[Edge Generation]: Name %s, End' % (res[0]))
    except Exception as e:
      raise e
    finally:
      self.db_handler.close()
      for name, proc in rel_proc_dict.items():
        proc.terminate()
      print('End of the generation process.')


def main():
  # test_main = TestMain(config.test_scheme)
  test_main = TestMain(config.zhihu_scheme)
  if test_main.db_exist():
    test_main.clear_db()
  else:
    test_main.create_db()
  test_main.main_proc()


if __name__ == '__main__':
  main()
