# -*- coding: utf-8 -*-

import sqlite3


class Store(object):
  '''
  connect db and store data
  '''
  def __init__(self, db_name):
    self.db_name = db_name
    self.conn    = None
    self.cursor  = None

  def connect(self):
    self.conn    = sqlite3.connect(db_name)
    self.cursor  = self.conn.cursor()

  def close(self):
    try:
      self.cursor.close()
      self.conn.close()
    except Exception as e:
      print(e)

  def create_tbl(self, sql):
    try:
      self.cursor.execute(sql)
      self.conn.commit()
    except Exception as e:
      print(e)

  def create_db(self, script):
    try:
      self.cursor.executescript(script)
      self.conn.commit()
    except Exception as e:
      print(e)

  def insert_one(self, sql, data=None):
    try:
      if data == None:
        self.cursor.execute(sql)
        self.conn.commit()
      else:
        self.cursor.execute(sql, data)
        self.conn.commit()
    except Exception as e:
      print(e)

  def insert_many(self, sql, datum):
    try:
      self.cursor.executemany(sql, datum)
      self.conn.commit()
    except Exception as e:
      print(e)

  def query(self, sql):
    try:
      self.cursor.execute(sql)
      val = self.cursor.fetchall()
      return val
    except Exception as e:
      return []
      print(e)
