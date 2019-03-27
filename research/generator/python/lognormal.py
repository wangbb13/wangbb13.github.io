#-*- coding: utf-8 -*-
# author: wangbb13
# create time: 2019-03-07 09:59
# version 0.1
import math
import random
import numpy as np
from scipy.stats import norm


class NGLognormal(object):
    """docstring for NGGauss"""
    def __init__(self, mu, sigma, dmin, dmax, nodes, edges):
        self.mu = mu
        self.sigma = sigma
        self.dmin = dmin
        self.dmax = dmax
        self.nodes = nodes
        self.edges = edges
        self.const_a = 1.0 / (self.sigma * np.sqrt(2 * np.pi))
        self.const_b = 2 * np.power(self.sigma, 2)
        # match edges, and build hash tables, etc
        self.pre_process()

    def gaussian_function(self, x):
        """
        cumulative distribution function
        """
        return self.const_a * np.exp(-np.power(x - self.mu, 2) / self.const_b)

    def gaussian_cdf_point(self, x):
        a = (np.log(x + 0.1) - self.mu) / self.sigma
        b = (np.log(x - 0.1) - self.mu) / self.sigma
        return norm.cdf(a) - norm.cdf(b)

    def pd_function(self, x):
        # return self.gaussian_function(x)
        return self.gaussian_cdf_point(x)

    def number_of_d1(self):
        __temp = [self.pd_function(_) for _ in range(self.dmin, self.dmax + 1)]
        return round(self.nodes * __temp[0] / sum(__temp))

    def number_of_dmax(self):
        __temp = [self.pd_function(_) for _ in range(self.dmin, self.dmax + 1)]
        # print('max degree =', self.dmax, 'sum(__temp) =', sum(__temp))
        return round(self.nodes * __temp[-1] / sum(__temp))

    def get_outd_list(self):
        __temp = [self.pd_function(_) for _ in range(self.dmin, self.dmax + 1)]
        # print('__temp:', __temp)
        # print('max degree =', self.dmax, 'sum(__temp) =', sum(__temp))
        __c = self.nodes / sum(__temp)
        return [round(__c * _) for _ in __temp]

    def current_edges(self):
        outd_list = self.get_outd_list()
        outd_edge = [round(_ * __) for _, __ in zip(outd_list, list(range(self.dmin, self.dmax + 1)))]
        return sum(outd_edge)

    def pre_process(self):
        self.match_edges()
        # print([self.pd_function(_) for _ in range(self.dmin, self.dmax + 1)])
        # print(self.get_outd_list())
        # do not change the order !!
        self.build_out_hash_tables()
        self.build_in_hash_tables()
        # print([self.pd_function(_) for _ in range(self.dmin, self.dmax + 1)])
        # print(self.get_outd_list())

    def match_edges(self):
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
        while self.number_of_d1() > 1:
            self.mu += 1
        while self.number_of_d1() < 1:
            self.mu -= 1
        while self.number_of_dmax() < 1:
            self.dmax -= 1
        while self.number_of_dmax() > 1:
            self.dmax += 1
        __edges = self.current_edges()
        print('dmax =', self.dmax, 'mu =', self.mu, 'current edges =', __edges, ' expected edges =', self.edges)
        return 
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
            print('adjust dmax =', self.dmax, 'mu =', self.mu, ' edges =', int(__edges))
        elif __edges > self.edges:
            __l, __r = self.dmin, self.dmax
            while __l < __r:
                self.dmax = int((__l + __r) / 2)
                __edges = self.current_edges()
                if __edges > self.edges:
                    __r = self.dmax
                else:
                    __l = self.dmax + 1
            self.dmax = __l - 1
            print('adjust dmax = ', self.dmax, 'mu =', self.mu, ' edges = ', __edges)

    def build_out_hash_tables(self):
        dnum = self.dmax - self.dmin + 1
        outd_list = self.get_outd_list()
        actual_edges = sum(outd_list)
        # build out-degree-cdf
        out_cdf = [0 for _ in range(dnum)]
        out_cdf[0] = outd_list[0]
        for _ in range(1, dnum):
            out_cdf[_] = out_cdf[_ - 1] + outd_list[_]
        for _ in range(dnum):
            out_cdf[_] /= actual_edges
        # build hash tables
        min_outdcdf_gap = 1.
        for _ in range(1, dnum):
            if out_cdf[_] - out_cdf[_ - 1] == 0:
                print(_, outd_list[_], outd_list[_ - 1])
            min_outdcdf_gap = min(min_outdcdf_gap, out_cdf[_] - out_cdf[_ - 1])
        hash_length = int(math.ceil(1.0 / min_outdcdf_gap)) + 1
        self.outd_hash_table = [self.dmin for _ in range(hash_length)]
        i, sum_cdf = 0, 0.0
        for j in range(hash_length):
            if sum_cdf <= out_cdf[i]:
                self.outd_hash_table[j] += i
            else:
                i += 1
                self.outd_hash_table[j] += i
            sum_cdf += min_outdcdf_gap
        self.outd_hash_table[-1] = self.dmax + 1
        # end hash tables, start bucket size
        out_bucket_size = 1
        self.out_partition = int(self.nodes / out_bucket_size)
        self.out_bound = [int(self.nodes * _ / self.out_partition) for _ in range(1, self.out_partition+1)]
        self.random_l = 0.0
        self.random_step = 1.0 / self.out_partition
        # for old get_out_degree
        self.d_index, self.d_number = 0, 0
        self.dnum = dnum
        self.simple_mf = outd_list
        self.min_outdcdf_gap = min_outdcdf_gap

    def in_hash_function(self, x):
        return int(x * self.hash_factor)

    def build_in_hash_tables(self):
        # build in-degree cdf and index
        self.dnum = self.dmax - self.dmin + 1
        self.simple_mf = self.get_outd_list()
        self.inj_cdf = [0] * (self.dnum + 1)
        self.inj_idx = [-1] * (self.dnum + 1)
        for _ in range(1, self.dnum + 1):
            __num = self.simple_mf[_-1]
            self.inj_idx[_] = self.inj_idx[_-1] + __num
            self.inj_cdf[_] = self.inj_cdf[_-1] + __num * (_ - 1 + self.dmin) # cumulative edges (degree * num)
        # self.inj_cdf[0] = self.dmin
        self.inj_cdf[0] = 0
        self.inj_idx[0] = 0
        self.inj_idx[-1] = self.nodes - 1
        self.min_incdf_step = 1.0
        for _ in range(self.dnum + 1):
            self.inj_cdf[_] = self.inj_cdf[_] / self.inj_cdf[-1]
            if _ > 0:
                # if self.inj_cdf[_] - self.inj_cdf[_-1] == 0.:
                #     print(_, self.inj_cdf[_], self.inj_cdf[_-1], self.simple_mf[_ - 1])
                self.min_incdf_step = min(self.min_incdf_step, self.inj_cdf[_] - self.inj_cdf[_-1])
        self.inj_cdf[-1] = self.inj_cdf[-2] + (1.0 - self.inj_cdf[-2]) / 2.0
        self.min_incdf_step = min(self.min_incdf_step, self.inj_cdf[-1] - self.inj_cdf[-2])
        # build hash tables
        self.hash_factor = int(math.ceil(1.0 / self.min_incdf_step))
        self.hash_index = [0 for _ in range(self.hash_factor + 3)]
        self.hash_index_next = [0 for _ in range(self.hash_factor + 3)]
        self.hash_cdf = [0 for _ in range(self.hash_factor + 3)]
        self.hash_cdf_next = [0 for _ in range(self.hash_factor + 3)]
        self.hash_ratio = [0 for _ in range(self.hash_factor + 3)]
        __pre_v, __pre_i, __len = 0, 0, len(self.inj_cdf)
        for __j in range(1, __len):
            __i = self.in_hash_function(self.inj_cdf[__j])
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

    def get_d(self):
        """
        get out-degree
        """
        return self.get_old_d()
        if self.nodes < self.out_partition:
            return self.get_old_d()
        else:
            if self.d_number <= self.out_bound[self.d_index]:
                random_number = self.random_l + random.random() / self.out_partition
            else:
                self.d_index += 1
                self.random_l += self.random_step
                random_number = self.random_l + random.random() / self.out_partition
            res_idx = min(round(random_number / self.min_outdcdf_gap), len(self.outd_hash_table) - 1)
            self.d_number += 1
            return self.outd_hash_table[int(res_idx)]

    def get_old_d(self):
        """
        get out_degree simply
        """
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
        """
        get a target node
        """
        y = max(random.random(), self.inj_cdf[0])
        y = min(y, self.inj_cdf[-1])
        __i = self.in_hash_function(y)
        if y >= self.hash_cdf[__i]:
            a = self.hash_index[__i]
            c = self.hash_cdf[__i]
            r = self.hash_ratio[__i]
        else:
            a = self.hash_index[__i - 1]
            c = self.hash_cdf[__i - 1]
            r = self.hash_ratio[__i - 1]
        try:
            ans = int(a) + int((y - c) * r)
        except ZeroDivisionError:
            ans = int(a)
        return ans

    def need_extend(self):
        return 0

    def is_special(self):
        return False
