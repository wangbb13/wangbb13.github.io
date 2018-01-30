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
  def __init__(self, nodes, lambd, lambd1=-1, min_degree=0, max_degree=-1, mid_degree=-1, threv=0.5):
    '''
    nodes: the number of nodes
    lambd: for in/out degree
    lambd1: optional, for out/int degree, two stages
    min_degree: min degree in the graph
    max_degree: max degree in the graph
    mid_degree: turning point in the degree distribution
    threv: total degree * threv = total degree of first stage 
    '''
    self.nodes  = nodes
    self.lambd  = lambd
    self.lambd1 = lambd1
    self.min_degree = min_degree
    self.max_degree = max_degree
    self.mid_degree = mid_degree
    self.threv = threv
    self.name = 'power_law'

  def get_name(self):
    return self.name

  def get_nodes(self):
    return self.nodes 

  def get_lambd(self):
    return self.lambd 

  def get_lambd1(self):
    return self.lambd1 

  def get_min_degree(self):
    return self.min_degree 

  def get_max_degree(self):
    return self.max_degree 

  def get_mid_degree(self):
    return self.mid_degree

  def set_nodes(self, n):
    self.nodes = int(n)

  def set_lambd(self, l):
    self.lambd = float(l) 

  def set_lambd1(self, l):
    self.lambd1 = float(l) 

  def set_min_degree(self, d):
    self.min_degree = int(d) 

  def set_max_degree(self, d):
    self.max_degree = int(d) 

  def set_mid_degree(self, d):
    self.mid_degree = int(d)

  def set_threv(self, n):
    self.threv = float(n)

  def get_last_rate(self, lambd, min_d, max_d):
    const = sum([x ** (-lambd) for x in range(min_d, max_d+1)])
    ans = (max_d ** (-lambd)) / const
    return ans

  def get_last_count(self, nodes, lambd, min_d, max_d):
    return round(nodes * self.get_last_rate(lambd, min_d, max_d))

  def get_node_count(self, nodes, lambd, min_d, max_d):
    '''
    return: rtn list
      rtn[i]: the number of nodes with degree i
    '''
    const = sum([x ** (-lambd) for x in range(min_d, max_d+1)])
    rate  = [((x ** (-lambd))/const) for x in range(min_d, max_d+1)]
    rtn   = [round(nodes * r) for r in rate]
    return rtn

  def get_every_degree_count(self):
    '''
    return: rtn list
      rtn[i]: the number of nodes with degree i, from degree 1
      scene : one stage
    '''
    # TODO: try catch
    assert self.max_degree > 0 
    const = sum([x ** (-self.lambd) for x in range(self.min_degree, self.max_degree+1)])
    rate  = [((x ** (-self.lambd))/const) for x in range(self.min_degree, self.max_degree+1)]
    rtn   = [round(self.nodes * r)]

  def get_every_degree_count_two_stage(self):
    '''
    return: rtn list
      rtn[i]: the number of nodes with degree i
      scene : two stages
    '''
    # TODO: try catch
    assert self.lambd1 > 0
    assert self.mid_degree > 0
    assert self.max_degree > 0
    const1 = sum([x ** (-self.lambd)  for x in range(self.min_degree, self.mid_degree)])
    const2 = sum([x ** (-self.lambd1) for x in range(self.mid_degree+1, self.max_degree)])
    const = const1 + const2
    rate  = [((x ** (-self.lambd))/const) for x in range(self.min_degree, self.mid_degree)] + [((x ** (-self.lambd1))/const) for x in range(self.mid_degree+1, self.max_degree)]
    rtn = [round(self.nodes * r) for r in rate]
    return rtn

  def get_total_degree(self, nodes, lambd, min_d, max_d):
    d_list = [x for x in range(min_d, max_d+1)]
    n_list = self.get_node_count(nodes, lambd, min_d, max_d)
    length = max_d - min_d + 1
    ans = 0
    for i in range(length):
      ans += (d_list[i] * n_list[i])
    return ans

  def dtmn_max_degree(self):
    try:
      assert self.lambd1 == -1 
    except AssertionError
      raise AssertionError('There should be one lambd paramter: lambd=%s, lambd1=%s' % (self.lambd, self.lambd1))
    l = self.min_degree
    r = self.nodes
    # determine r, s.t. count(nodes of degree i (i <- [1, r))) > 0
    while l < r:
      mid = int((l + r) / 2)
      end_n = self.get_last_count(self.nodes, self.lambd, l, mid)
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
      node_sum = sum(self.get_node_count(self.nodes, self.lambd, l, mid))
      if node_sum > self.nodes:
        r = mid
      # elif node_sum == self.nodes:
      #   r = mid + 1
      #   break
      else:
        l = mid + 1
    return max((r - 1), 0)

  def dtmn_max_degree_2(self, total_degree):
    '''
    input:  lambd, lambd1, min_degree, max_degree
    return: (maxk1, maxk2, list)
            maxk1: for degree in [0, maxk1], match the lambd1
            maxk2: for degree in [maxk1, maxk2], match the lambd2
            list: list[i], the number of nodes with degree i
    '''
    try:
      assert self.lambd1 != -1 
    except AssertionError:
      raise AssertionError('There should be two lambd parameters(greater than 0): lambd=%s, lambd1=%s\n' % (self.mid_degree, self.max_degree))
    degree_s1  = round(total_degree * self.threv)
    l = self.min_degree 
    r = self.nodes 
    # determine degree d, s.t. total degree <= degree_s1 
    while l < r:
      mid = int((l + r) / 2)
      dgs = self.get_total_degree(self.nodes, self.lambd, l, mid)
      if dgs < degree_s1:
        l = mid + 1
      elif dgs == degree_s1:
        r = mid + 1
        break
      else:
        r = mid
    max_d21 = max(r - 1, 1)
    rtn_list = self.get_node_count(self.nodes, self.lambd, self.min_degree, max_d21)
    alllow_degree = total_degree - self.get_total_degree(self.nodes, self.lambd, self.min_degree, max_d21)
    last_rate = self.get_last_rate(self.lambd, self.min_degree, max_d21)
    # compute stage 2, corresponding with lambd2
    const = math.log(last_rate) + self.lambd1 * math.log(max_d21)
    cur_tot = 0
    max_d22 = max_d21
    while cur_tot < alllow_degree:
      max_d22 += 1
      log_p = (-self.lambd1) * math.log(max_d22) + const
      cnt = max(round(self.nodes * (math.exp(log_p))), self.min_degree)
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
