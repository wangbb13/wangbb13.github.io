# -*- coding: utf-8 -*- 
import random
import math


class PWL(object):
  '''
  power law distribution
  y_i: the proportion of nodes with degree i
  x_i: the degree i
  then x_i ^ (lambda) * y_i = const
  so how to determine y_i:
  denominator = Sigma(i := 1 to N) (x_i ^ (-lambda))
  y_i = x_i ^ (-lambda) / denominator
  '''
  def __init__(self, nodes, lambd, lambd1=-1, min_degree=-1, max_degree=-1, lambd1=-1, lambd2=-1, min_degree_2=-1, max_degree_2=-1, threv=0.5):
    '''
    nodes: the number of nodes
    lambd: for in/out degree
    lambd1, lambd2: for out/int degree
    three parameters for balance
    max_d1: the max degree corresponding with lambd and nodes
    '''
    self.nodes  = nodes
    self.lambd  = lambd
    self.min_degree = min_degree
    self.max_degree = max_degree
    self.lambd1 = lambd1
    self.lambd2 = lambd2
    self.min_degree_2 = min_degree_2
    self.max_degree_2 = max_degree_2
    self.threv  = threv
    self.max_d1  = -1 
    self.max_d21 = -1 
    self.max_d22 = -1 

  def set_nodes(self, n):
    self.nodes = n

  def set_lambd(self, l):
    self.lambd = l 

  def set_lambd1(self, l):
    self.lambd1 = l 

  def set_lambd2(self, l):
    self.lambd2 = l 

  def set_threv(self, val):
    self.threv = val

  def get_last_rate(self, nodes, degree, lambd):
    const = sum([x ** (-lambd) for x in range(1, degree+1)])
    ans = (degree ** (-lambd)) / const
    return ans

  def get_last_count(self, nodes, degree, lambd):
    const = sum([x ** (-lambd) for x in range(1, degree+1)])
    ans = round(nodes * ((degree ** (-lambd)) / const))
    return ans

  def get_node_count(self, nodes, degree, lambd):
    const = sum([x ** (-lambd) for x in range(1, degree+1)])
    rate  = [((x ** (-lambd))/const) for x in range(1, degree+1)]
    rtn   = [round(nodes * r) for r in rate]
    return rtn

  def get_total_degree(self, nodes, degree, lambd):
    d_list = [x for x in range(1, degree+1)]
    n_list = self.get_node_count(nodes, degree, lambd)
    ans = 0
    for i in range(degree):
      ans += (d_list[i] * n_list[i])
    return ans

  def dtmn_max_degree(self):
    l = 1
    r = self.nodes
    # determine r, s.t. count(nodes of degree i (i <- [1, r))) > 0
    while l < r:
      mid = int((l + r) / 2)
      end_n = self.get_last_count(self.nodes, mid, self.lambd)
      if end_n == 0:
        r = mid
      else:
        l = mid + 1
    # determine r s.t. total number of nodes <= the number of nodes
    r -= 1
    l = int(r / 2)
    # print('ans r: ', r)
    while l < r:
      mid = int((l + r) / 2)
      node_sum = sum(self.get_node_count(self.nodes, mid, self.lambd))
      if node_sum > self.nodes:
        r = mid
      # elif node_sum == self.nodes:
      #   r = mid + 1
      #   break
      else:
        l = mid + 1
    self.max_d1 = max((r - 1), 0)

  def dtmn_max_degree_2(self):
    '''
    return: (maxk1, maxk2, list)
            maxk1: for degree in [0, maxk1], match the lambd1
            maxk2: for degree in [maxk1, maxk2], match the lambd2
            list: list[i], the number of nodes with degree i
    '''
    try:
      assert self.lambd1 != -1 and self.lambd2 != -1
    except AssertionError:
      raise AssertionError('There is no lambd1 and lambd2 parameter.')
    all_degree = self.get_total_degree(self.nodes, self.max_d1, self.lambd)
    degree_s1  = round(all_degree * self.threv)
    l = 1
    r = self.max_d1
    # determine degree d, s.t. total degree <= degree_s1
    while l < r:
      mid = int((l + r) / 2)
      dgs = self.get_total_degree(self.nodes, mid, self.lambd1)
      if dgs < degree_s1:
        l = mid + 1
      elif dgs == degree_s1:
        r = mid + 1
        break
      else:
        r = mid
    max_d21 = max(r - 1, 1)
    rtn_list = self.get_node_count(self.nodes, max_d21, self.lambd1)
    alllow_degree = all_degree - self.get_total_degree(self.nodes, max_d21, self.lambd1)
    last_rate = self.get_last_rate(self.nodes, max_d21, self.lambd1)
    # compute stage 2, corresponding with lambd2
    const = math.log(last_rate) + self.lambd2 * math.log(max_d21)
    cur_tot = 0
    max_d22 = max_d21
    while cur_tot < alllow_degree:
      max_d22 += 1
      log_p = (-self.lambd2) * math.log(max_d22) + const
      cnt = max(round(self.nodes * (math.exp(log_p))), 1)
      rtn_list.append(cnt)
      cur_tot += (max_d22 * cnt)
    return (max_d21, max_d22, rtn_list)


def test():
  while True:
    nodes = int(input())
    # tau   = float(input())
    pwl = PWL(nodes, 1.49, 1.15, 2.7)
    pwl.dtmn_max_degree()
    k1, k2, _ = pwl.dtmn_max_degree_2()
    print('%-4d %-4d %-4d' % (pwl.max_d1, k1, k2))
    


if __name__ == '__main__':
    test()
