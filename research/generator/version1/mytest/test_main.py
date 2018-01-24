# -*- coding: utf-8 -*-
import os
import sys
sys.path.append('../')

from multiprocessing import Pipe, Value, Array, Process

from model import tbl_sql, delete_sql, count_size, Store
from gen import GenDDR, GenFE
import mytest.config as config


class TestMain(object):
  '''
  test full process
  '''
  def __init__(self, scheme):
    self.scheme = scheme
    self.db_name = scheme['alias'] + '.db'
    self.db_handler = Store(self.db_name)
    self.db_handler.connect()

  def create_db(self):
    try:
      crt_db_sql = tbl_sql(self.scheme)
      with open('ddl.sql', 'w') as f:
        f.write(crt_db_sql)
      self.db_handler.execute_script(crt_db_sql)
      print('[create db %s]: done' % (self.db_name))
    except Exception as e:
      raise e

  def clear_db(self):
    try:
      dlt_sql = delete_sql(self.scheme)
      self.db_handler.execute_script(dlt_sql)
      print('[clear db %s]: done' % (self.db_name))
    except Exception as e:
      raise e

  def test_follow(self, mode='local'):
    user_id = 0
    ent_size = count_size(self.scheme)
    s_conn, c_conn = Pipe()
    rel_dic = self.scheme['relation'][0]
    src_dic = self.scheme['entity'][0]
    user_gen = GenFE(src_dic, ent_size, self.db_name)
    gen_follow = GenDDR(self.db_name, rel_dic, c_conn, src_dic, ent_size, mode=mode)
    gen_p = Process(target=gen_follow.start)
    gen_p.start()
    try:
      if mode == 'local':
        while True:
          val = s_conn.recv()
          if val[0] == 2:
            user_gen.start(val[1])
            user_id += val[1]
            print('[Gen User ID]: %d' % (user_id))
          elif val[0] == -1:
            print('[Gen fake size]: %d' % (val[1]))
            break
      elif mode == 'u-level':
        pass
    except Exception as e:
      raise e
    finally:
      self.db_handler.close()
      gen_p.terminate()
      print('[generate end]')


def main():
  test_main = TestMain(config.test_scheme)
  # if os.path.exists('./opera.db'):
  #   os.system('rm ./opera.db')
  test_main.create_db()
  test_main.test_follow()


if __name__ == '__main__':
  main()