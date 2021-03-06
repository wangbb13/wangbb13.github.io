# -*- coding: utf-8 -*-
import random
import math

class Uniform(object):
  '''
  uniform
  '''
  def __init__(self, nodes, min_val, max_val):
    self.nodes = nodes
    self.minv = min_val
    self.maxv = max_val
    self.name = 'uniform'

  def get_name(self):
    return self.name

  def get_max_degree(self):
    return self.maxv

  def get_min_degree(self):
    return self.minv

  def get_nodes(self):
    return self.nodes

  def set_min_degree(self, n):
    self.minv = n 

  def set_max_degree(self, n):
    self.maxv = n 

  def set_nodes(self, n):
    self.nodes = n 

  def get_every_degree_count(self):
    '''
    return: rtn list
      rtn[i] : the number of node with degree i
    '''
    degree_num = self.maxv - self.minv + 1 
    rtn = [0] * degree_num
    mean = int(self.nodes / degree_num)
    for i in range(degree_num):
      rtn[i] = mean
    idx_list = list(range(degree_num))
    random.shuffle(idx_list)
    remain = self.nodes - degree_num * mean
    for i in range(remain):
      rtn[idx_list[i]] += 1 
    return rtn
