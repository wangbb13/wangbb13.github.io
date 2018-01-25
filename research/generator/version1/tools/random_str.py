# -*- coding: utf-8 -*-
import random
from datetime import datetime, timedelta

alphabet = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_.'
nrof_alphabet = len(alphabet)
alphabet_index = list(range(nrof_alphabet))
standard_time_format = '%Y-%m-%d %H:%M:%S.%f'

def random_str(length):
  l = alphabet_index[:]
  random.shuffle(l)
  return ''.join([alphabet[i] for i in l[:length]])


def random_time(start_time, seconds):
  '''
  return str
  '''
  return str(start_time + timedelta(0, random.randint(0, seconds))).split('.')[0]

