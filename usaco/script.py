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
    string = ''
    with open('template.cpp', 'r') as f:
      string = f.read()
    with open('%s.cpp'%(name), 'w') as f:
      filename = os.path.basename(name)
      f.write(string.replace('[]', filename))
    # os.system('cp template.cpp %s.cpp' % (name))
    os.system('touch %s.in %s.out' % (name, name))
    os.system('subl -a %s.cpp %s.in %s.out' % (name, name, name))
    print('create successfully.')
  elif cmd == 'd':
    os.system('rm %s.in %s.out %s' % (name, name, name))
    print('delete successfully.')
  else:
    print('unkonwn command.')
  exit(0)
