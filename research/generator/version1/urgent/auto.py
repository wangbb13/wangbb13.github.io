# -*- coding: utf-8 -*- 
# function: replace number in data with specific content
import random
import os
# laod candidate content
cad_sta = 'cad_status.txt'
cad_cmt = 'cad_comments.txt'

try:
  status  = [s.strip() for s in open(cad_sta, 'r').readlines()]
  cmts    = [s.strip() for s in open(cad_cmt, 'r').readlines()]
except Exception as e:
  raise e


def process(file, tmp, cad):
  assert file != tmp
  assert os.path.isfile(file)
  assert len(cad) > 0
  fh = open(tmp, 'w')
  with open(file, 'r') as f:
    for s in f.readlines():
      l = s.strip().split('#')
      idx = int(l[2]) - 1
      try:
        l[2] = cad[idx]
      except:
        l[2] = cad[random.randint(0, len(cad) - 1)]
      fh.write('#'.join(l) + '\n')
  fh.close()
  os.remove(file)
  os.rename(tmp, file)


def main():
  # feed.txt
  tmp = 'feed.txt.txt'
  file = 'feed.txt'
  process(file, tmp, status)
  # comment.txt
  tmp = 'comment.txt.txt'
  file = 'comment.txt'
  process(file, tmp, cmts)
  print('done.')


if __name__ == '__main__':
  main()
