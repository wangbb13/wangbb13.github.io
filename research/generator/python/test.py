# create time : 2018-04-18
# author : wangbb13
import math
import time
import numpy as np
import matplotlib.pyplot as plt
from visualization import get_rand_color
from pwl import NGPowerLaw


def get_cdf(n, lmd):
    lmd = -lmd
    cdf = [0] * (n + 1)
    cdf[1] = 1 ** lmd
    for i in range(2, n+1):
        cdf[i] = cdf[i-1] + i ** lmd
    return cdf


def f1(y, lmd):
    lmd = -lmd
    x = math.pow((lmd+1) * y + 1, 1/(lmd+1))
    return math.ceil(x)


def f2(y, lmd):
    lmd = -lmd
    x = math.pow((lmd+1) * y - lmd, 1/(lmd+1))
    return math.floor(x)


def test():
    lmd = 1.2
    num = 50
    cdf = get_cdf(num, lmd)
    x = np.asarray([_ for _ in range(1, num+1)])
    y = np.asarray(cdf[1:])
    plt.scatter(x, y, marker='.', color=get_rand_color(), linewidths=2)
    plt.show()


class UnitTestForPWL(object):
    """docstring for UnitTestForPWL"""
    def __init__(self, lmd, dmin, dmax, nodes, edges):
        self.pwl = NGPowerLaw(lmd, dmin, dmax, nodes, edges)

    def pairwise_compare(self, n):
        for _ in range(n):
            rv = self.pwl.gen_uniform()
            a = self.pwl.__get_j__(rv)
            # print('getj =', a)
            b = self.pwl.__hash_get_j__(rv)
            # print('hash =', b)
            if a != b:
                print('random value =', rv)
                print('getj =', a)
                print('hash =', b)

    def func_time(self, f, n):
        start = time.time()
        for _ in range(n):
            rv = self.pwl.gen_uniform()
            f(rv)
        end = time.time()
        print('running time: ', (end - start))

    def run(self):
        n = 1000000
        # self.pairwise_compare(n)
        print('getj', end=' ')
        self.func_time(self.pwl.__get_j__, n)
        print('hash', end=' ')
        self.func_time(self.pwl.__hash_get_j__, n)
        print('null', end=' ')
        self.func_time(lambda x: x + 1, n)
        # while True:
        #     x = input('yes/no> ')
        #     if x == 'n':
        #         break
        #     else:
        #         self.pairwise_compare(1)


def test_pwl():
    # tp = NGPowerLaw(1.15, 1, 1000, 5000000, 1000000000)
    # cdf = tp.get_cdf()
    # j = len(cdf)
    # print('length =', j)
    # min_val = 1.0
    # for _ in range(j - 1):
    #     min_val = min(min_val, cdf[_+1] - cdf[_])
    #     if cdf[_+1] < cdf[_]:
    #         print('exception: ', _, cdf[_], cdf[_+1])
    # print('min_val =', min_val)
    # print('mathematical =', cdf[-1] - cdf[-2])
    # print('first 2:', cdf[:2])
    ut = UnitTestForPWL(1.15, 1, 1000, 5000000, 1000000000)
    ut.run()


def main():
    test_pwl()


if __name__ == '__main__':
    main()
