# -*- coding: utf-8 -*- 
import os
import sys

from multiprocessing import Pipe, Process

from model import tbl_sql, delete_sql, count_size, Store
from gen import GenDDR, GenFE


class Main(object):
  '''
  main procedure
  Input : scheme
  Output: social network data, saved to sqlite
  '''
  def __init__(self, scheme):
    self.scheme  = scheme
    self.db_name = scheme['alias'] + '.db'
    self.db_handler = Store(self.db_name)
    self.db_handler.connect()

  def create_db(self):
    try:
      crt_db_sql = tbl_sql(self.scheme)
      # with open('ddl.sql', 'w') as f:
      #   f.write(crt_db_sql)
      self.db_handler.execute_script(crt_db_sql)
      print('Create db %s done' % self.db_name)
    except Exception as e:
      raise e

  def clear_db(self):
    try:
      dlt_sql = delete_sql(self.scheme)
      self.db_handler.execute_script(dlt_sql)
      print('clear db %s done' % (self.db_name))
    except Exception as e:
      raise e

  def process(self):
    pass
