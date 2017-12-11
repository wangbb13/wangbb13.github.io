# -*- coding: utf-8 -*-
import sys
sys.path.append('../')

from analyse import Analyses
import config

def main():
  rel = config.test_scheme['relation'][0]
  db_name = config.test_scheme['alias'] + '.db'
  in_ = int(input('in  nodes: '))
  out = int(input('out nodes: '))
  analyse_self = Analyses(rel, db_name, in_, out)
  res = analyse_self.analyse()
  print(res)


if __name__ == '__main__':
  main()