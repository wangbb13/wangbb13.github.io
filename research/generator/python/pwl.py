# -*- coding: utf-8 -*-
# author: wangbb13
# create time: 2018-12-04 14:12
# add hash function: 2019-01-24 10:00 A.M
import math
import random
from utility import bin_search


class NGPowerLaw(object):
    def __init__(self, lmd, dmin, dmax, nodes, edges):
        self.lmd = -abs(lmd)
        self.dmin = dmin
        self.dmax = dmax
        self.nodes = nodes
        self.edges = edges
        self.select_p = 0
        self.pre_processing()
        # for out-degree in memory
        __temp = [_ ** self.lmd for _ in range(self.dmin, self.dmax + 1)]
        __c = self.nodes / sum(__temp)
        self.simple_mf = [int(__c * _) for _ in __temp] # number of nodes with degree _
        actual_edges = sum(self.simple_mf)
        print('For Out Nodes =', actual_edges)
        self.d_index, self.d_number = 0, 0
        # out-degree hash tables
        self.dnum = self.dmax - self.dmin + 1
        self.out_cdf = [0 for _ in range(self.dnum)]
        self.out_cdf[0] = self.simple_mf[0]
        for _ in range(1, self.dnum):
            self.out_cdf[_] = self.out_cdf[_ - 1] + self.simple_mf[_]
        for _ in range(self.dnum):
            self.out_cdf[_] /= actual_edges
        self.process_out_degree()

        # for in-degree in memory
        # self.dnum = self.dmax - self.dmin + 1
        self.inj_cdf = [0] * (self.dnum + 1)
        self.inj_idx = [-1] * (self.dnum + 1)
        for _ in range(1, self.dnum + 1):
            __num = self.simple_mf[_-1]
            self.inj_idx[_] = self.inj_idx[_-1] + __num
            self.inj_cdf[_] = self.inj_cdf[_-1] + __num * (_ - 1 + self.dmin) # cumulative edges (degree * num)
        self.inj_cdf[0] = self.dmin
        self.inj_idx[0] = 0
        self.inj_idx[-1] = self.nodes - 1
        self.min_cdf_step = 1.0
        for _ in range(self.dnum + 1):
            self.inj_cdf[_] = self.inj_cdf[_] / self.inj_cdf[-1]
            if _ > 0:
                self.min_cdf_step = min(self.min_cdf_step, self.inj_cdf[_] - self.inj_cdf[_-1])
        self.inj_cdf[-1] = self.inj_cdf[-2] + (1.0 - self.inj_cdf[-2]) / 2.0
        self.min_cdf_step = min(self.min_cdf_step, self.inj_cdf[-1] - self.inj_cdf[-2])
        self.post_processing()
        # print('inj_cdf', self.inj_cdf)
        # print('inj_idx', self.inj_idx)

    def post_processing(self):
        """
        For bulding hash function
        """
        digits = 0
        __temp = self.min_cdf_step
        while __temp < 1.0:
            digits -= 1
            __temp *= 10
        self.adjust_min_cdf_step = 10 ** digits
        print('min_cdf_step =', self.min_cdf_step, 'adjust_min_step =', self.adjust_min_cdf_step)
        self.hash_factor = 10 ** (-digits)
        # build hash function
        self.hash_index = [0 for _ in range(self.hash_factor + 3)]
        self.hash_index_next = [0 for _ in range(self.hash_factor + 3)]
        self.hash_cdf = [0 for _ in range(self.hash_factor + 3)]
        self.hash_cdf_next = [0 for _ in range(self.hash_factor + 3)]
        self.hash_ratio = [0 for _ in range(self.hash_factor + 3)]
        __pre_v, __pre_i, __len = 0, 0, len(self.inj_cdf)
        for __j in range(1, __len):
            __i = self.hash_function(self.inj_cdf[__j])
            for _ in range(__pre_i, __i):
                self.hash_index[_] = __pre_v
                self.hash_index_next[_] = self.inj_idx[__j]
                self.hash_cdf[_] = self.inj_cdf[__j - 1]
                self.hash_cdf_next[_] = self.inj_cdf[__j]
                self.hash_ratio[_] = (self.hash_index_next[_] - self.hash_index[_]) / (self.hash_cdf_next[_] - self.hash_cdf[_])
            __pre_v = self.inj_idx[__j] 
            __pre_i = __i 
        for _ in range(__pre_i, self.hash_factor + 3):
            self.hash_index[_] = __pre_v
            self.hash_index_next[_] = self.nodes - 1
            self.hash_cdf[_] = self.inj_cdf[__len - 1]
            self.hash_cdf_next[_] = 1.0 
            self.hash_ratio[_] = (self.hash_index_next[_] - self.hash_index[_]) / (self.hash_cdf_next[_] - self.hash_cdf[_])
        # print(self.inj_idx)
        # print(self.inj_cdf)
        # print(self.hash_index)
        # print(self.hash_index_next)
        # print(self.hash_cdf)
        # print(self.hash_cdf_next)

    def hash_function(self, x):
        return int(x * self.hash_factor)

    def gen_uniform(self):
        res = max(random.random(), self.inj_cdf[0])
        res = min(res, self.inj_cdf[-1])
        return res

    def __get_j__(self, rv):
        y = rv
        i = bin_search(self.inj_cdf, y)
        i = min(i, self.dnum)
        if self.inj_cdf[i] > y:
            a = self.inj_idx[i - 1]
            b = self.inj_idx[i]
            c = self.inj_cdf[i - 1]
            d = self.inj_cdf[i]
            try:
                ans = a + int((y - c) * (b - a) / (d - c))
            except ZeroDivisionError:
                ans = a
        else:
            ans = self.inj_idx[i]
        return ans

    def __hash_get_j__(self, rv):
        __i = self.hash_function(rv)
        if rv >= self.hash_cdf[__i]:
            a = self.hash_index[__i]
            # b = self.hash_index_next[__i]
            c = self.hash_cdf[__i]
            # d = self.hash_cdf_next[__i]
            r = self.hash_ratio[__i]
        else:
            a = self.hash_index[__i - 1]
            # b = self.hash_index[__i]
            c = self.hash_cdf[__i - 1]
            # d = self.hash_cdf[__i]
            r = self.hash_ratio[__i - 1]
        # print('index: ', a, b)
        # print('value: ', c, d)
        try:
            # ans = a + int((rv - c) * (b - a) / (d - c))
            ans = a + int((rv - c) * r)
        except ZeroDivisionError:
            ans = a
        return ans

    def get_cdf(self):
        return self.inj_cdf

    def number_of_dmax(self):
        """
        :return: number of nodes with maximum degree
        """
        __bbs = self.dmax ** self.lmd
        __sum = sum([_ ** self.lmd for _ in range(self.dmin, self.dmax)]) + __bbs
        return self.nodes * (__bbs / __sum)

    def current_edges(self):
        """
        :return: number of edges with current parameters
        """
        __temp = [_ ** self.lmd for _ in range(self.dmin, self.dmax+1)]
        __c = self.nodes / sum(__temp)
        return __c * sum([_ * __ for _, __ in zip(__temp, list(range(self.dmin, self.dmax+1)))])

    def pre_processing(self):
        """
        0. reduce dmax s.t. number_of_dmax() >= 1
        1. calculate current edges c_e
        case 1: c_e < edges
            extend dmax
            case 1.1: stop when number_of_dmax() < 1
            case 1.2: stop when c_e >= edges
        case 2: c_e > edges
            edges -> c
            c -> nodes'
            select_p = nodes' / node

            modify: adjust dmax
        :return:
        """
        while self.number_of_dmax() < 1:
            self.dmax -= 1
        __edges = self.current_edges()
        print('current edges =', __edges, ' expected edges =', self.edges)
        if __edges < self.edges:
            __temp = self.dmax
            __l = self.dmax
            self.dmax *= 2
            __r = self.dmax
            while self.number_of_dmax() >= 1 and __r < self.nodes:
                __l = __r
                self.dmax *= 2
                __r = self.dmax
            while __l < __r:
                self.dmax = int((__l + __r) / 2)
                if self.number_of_dmax() < 1:
                    __r = self.dmax
                else:
                    __l = self.dmax + 1
            self.dmax = __l - 1
            __edges = self.current_edges()
            if __edges > self.edges:
                __l = __temp
                __r = self.dmax
                while __l < __r:
                    self.dmax = int((__l + __r) / 2)
                    __edges = self.current_edges()
                    if __edges > self.edges:
                        __r = self.dmax
                    else:
                        __l = self.dmax + 1
                self.dmax = __l - 1
            print('adjust dmax =', self.dmax, ' edges =', int(__edges))
        elif __edges > self.edges:
            # __temp1 = [_ ** self.lmd for _ in range(self.dmin, self.dmax + 1)]
            # __temp2 = [_ * __ for _, __ in zip(__temp1, list(range(self.dmin, self.dmax+1)))]
            # c = self.edges / sum(__temp2)
            # n = c * sum(__temp1)
            # self.select_p = n / self.nodes
            # print('reduce select p =', self.select_p)
            __l, __r = self.dmin, self.dmax
            while __l < __r:
                self.dmax = int((__l + __r) / 2)
                __edges = self.current_edges()
                if __edges > self.edges:
                    __r = self.dmax
                else:
                    __l = self.dmax + 1
            self.dmax = __l - 1
            print('adjust dmax = ', self.dmax, ' edges = ', __edges)

    def process_out_degree(self):
        self.min_outcdf_gap = 1.
        for _ in range(1, self.dnum):
            self.min_outcdf_gap = min(self.min_outcdf_gap, self.out_cdf[_] - self.out_cdf[_ - 1])
        hash_length = int(math.ceil(1.0 / self.min_outcdf_gap))
        self.hash_out_deg = [self.dmin for _ in range(hash_length + 1)]
        i, sum_cdf = 0, 0.0
        for j in range(hash_length):
            if sum_cdf <= self.out_cdf[i]:
                self.hash_out_deg[j] += i
            else:
                i += 1
                self.hash_out_deg[j] += i
            sum_cdf += self.min_outcdf_gap
        self.hash_out_deg[hash_length] = self.dmax + 1
        out_bucket_size = 100
        self.out_partition = int(self.nodes / out_bucket_size)
        self.out_bound = [int(self.nodes * _ / self.out_partition) for _ in range(1, self.out_partition+1)]
        self.random_l = 0.0
        self.random_step = 1.0 / self.out_partition

    def get_d(self):
        # return self.get_d_old()
        if self.nodes < self.out_partition:
            return self.get_d_old()
        else:
            if self.d_number <= self.out_bound[self.d_index]:
                random_number = self.random_l + random.random() / self.out_partition
            else:
                self.d_index = (self.d_index + 1) % (len(self.out_bound))
                self.random_l += self.random_step
                random_number = self.random_l + random.random() / self.out_partition
            res_idx = min(round(random_number / self.min_outcdf_gap), len(self.hash_out_deg) - 1)
            self.d_number += 1
            if self.d_number == self.nodes:
                self.d_number = 0
                self.d_index = 0
                self.random_l = 0.0
            return self.hash_out_deg[res_idx]

    def get_d_old(self):
        if self.select_p > 0:
            if random.random() > self.select_p:
                return 0
        if self.d_index < self.dnum:
            if self.d_number < self.simple_mf[self.d_index]:
                self.d_number += 1
            else:
                self.d_number = 1
                self.d_index += 1
            return self.d_index + self.dmin
        else:
            return self.d_index + self.dmin - 1

    def get_j(self):
        y = self.gen_uniform()
        return self.__hash_get_j__(y)
        # i = bin_search(self.inj_cdf, y)
        # i = min(i, self.dnum)
        # if self.inj_cdf[i] > y:
        #     a = self.inj_idx[i - 1]
        #     b = self.inj_idx[i]
        #     c = self.inj_cdf[i - 1]
        #     d = self.inj_cdf[i]
        #     try:
        #         ans = a + int((y - c) * (b - a) / (d - c))
        #     except ZeroDivisionError:
        #         ans = a
        # else:
        #     ans = self.inj_idx[i]
        # return ans

    def need_extend(self):
        return 0

    def is_special(self):
        return False
