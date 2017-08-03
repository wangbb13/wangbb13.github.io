# -*- coding: utf-8 -*-

import sys
import os

if __name__ == '__main__':
  if len(sys.argv) != 3:
    print('usage: python3 script.py [prog_name] [c|d]')
    print('c means create, while d means delete')
    exit(0)
  cmd = sys.argv[2]
  name = sys.argv[1]
  if cmd == 'c':
    os.system('cp template.cpp %s.cpp' % (name))
    os.system('touch %s.in %s.out' % (name, name))
    os.system('subl -a %s.cpp %s.in %s.out' % (name, name, name))
    print('create successfully.')
  elif cmd == 'd':
    os.system('rm %s %s.in %s.out' % (name, name, name))
    print('delete successfully.')
  else:
    print('unkonwn command.')
  exit(0)
