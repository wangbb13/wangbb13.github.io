# -*- coding: utf-8 -*-

print('feed')
with open('feed.txt', 'r') as f:
  sta_id = set()
  for line in f.readlines():
    sta_id.add(int(line.split('status')[1]))
  print('max: ', max(sta_id))
  print('min', min(sta_id))
  print('len', len(sta_id))


print('comment')
with open('comment.txt', 'r') as f:
  sta_id = set()
  for line in f.readlines():
    sta_id.add(int(line.split('#')[0].split('status')[1]))
  print('max', max(sta_id))
  print('min', min(sta_id))
  # print(len(sta_id))


print('thumbup')
with open('thumbup.txt', 'r') as f:
  sta_id = set()
  for line in f.readlines():
    sta_id.add(int(line.split('#')[0].split('status')[1]))
  print('max', max(sta_id))
  print('min', min(sta_id))
  # print(len(sta_id))
