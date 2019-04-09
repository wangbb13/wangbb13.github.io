#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

typedef unsigned long long int ullint;

class NGPowerLow
{
private:
    double lambda;
    int dmin;
    int dmax;
    int nodes;
    ullint edges;
    int drange;

    // random number
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution;

    // for out-degree
    int d_index, d_number;
    std::vector<int> simple_mf;

    // for in-degree
    double hash_factor;
    std::vector<double> inj_cdf;
    std::vector<int> inj_idx;
    std::vector<double> hash_cdf;
    std::vector<int> hash_index;
    std::vector<double> hash_ratio;

private:
    void pre_processing();
    void post_processing();
    double gen_uniform();
    int hash_function(double);
    int number_of_dmax();
    ullint current_edges();

public:
    int get_d();
    int get_j();
    NGPowerLow(double, int, int, int, ullint);
    ~NGPowerLow() {}
};

NGPowerLow::NGPowerLow(double _lambda, int _dmin, int _dmax, int _nodes, ullint _edges) {
    lambda = -abs(_lambda);
    dmin = _dmin;
    dmax = _dmax;
    nodes = _nodes;
    edges = _edges;
    
    // for generating random number
    distribution = std::uniform_real_distribution<double>(0.0, 1.0);

    pre_processing();

    // for out-degree in memory
    drange = dmax - dmin + 1;
    std::vector<double> __temp(drange);
    double __sum = 0.0;
    for (int i = dmin; i <= dmax; ++ i) {
        __temp[i - dmin] = pow(i * 1.0, lambda);
        __sum += __temp[i - dmin];
    }
    double __c = nodes / __sum;
    simple_mf.resize(drange);
    for (int i = 0; i < drange; ++ i) 
        simple_mf[i] = (int)(__c * __temp[i]);
    d_index = 0;
    d_number = 0;

    // for in-degree in memory
    post_processing();
}

int NGPowerLow::number_of_dmax() {
    double __bbs = pow(dmax * 1.0, lambda);
    double __sum = 0.0;
    for (int i = dmin; i < dmax; ++ i) {
        __sum += pow(i * 1.0, lambda);
    }
    return (int)(nodes * (__bbs / (__bbs + __sum)));
}

ullint NGPowerLow::current_edges() {
    // TODO: some problems
    double __sum = 0.0, __zip = 0.0, __t;
    int range = dmax - dmin + 1;
    double *p = new double[range];
    for (int i = dmin; i <= dmax; ++ i) {
        __t = pow(i * 1.0, lambda);
        __sum += __t;
        p[i - dmin] = __t;
        // __zip += i * __t;
    }
    double __c = nodes / __sum;
    ullint ans = 0;
    for (int i = 0; i < range; ++i) {
        ans += (ullint)(__c * p[i] * (i + dmin));
    }
    return ans;
}

void NGPowerLow::pre_processing() {
    while (number_of_dmax() < 1) 
        dmax -= 1;
    ullint __edges = current_edges();
    // print mid information
    std::cout << "current edges = " << __edges << " expected edges = " << edges << std::endl;
    // print end
    if (__edges < edges) {
        int __temp = dmax, __l = dmax, __r = (dmax *= 2);
        while (number_of_dmax() >= 1 && __r < nodes) {
            __l = __r;
            __r = (dmax *= 2);
        }
        if (__r > nodes)
            __r = nodes;
        while (__l < __r) {
            dmax = (__l + __r) / 2;
            if (number_of_dmax() < 1) 
                __r = dmax;
            else
                __l = dmax + 1;
        }
        dmax = __l - 1;
        __edges = current_edges();
        if (__edges > edges) {
            __l = __temp;
            __r = dmax;
            while (__l < __r) {
                dmax = (__l + __r) / 2;
                __edges = current_edges();
                if (__edges > edges)
                    __r = dmax;
                else
                    __l = dmax + 1;
            }
            dmax = __l - 1;
        }
        // print adjust edges
        std::cout << "adjust dmax = " << dmax << " edges = " << __edges << std::endl;
        // print end
    } else if (__edges > edges) {
        int __l = dmin, __r = dmax;
        while (__l < __r) {
            dmax = (__l + __r) / 2;
            __edges = current_edges();
            if (__edges > edges) 
                __r = dmax;
            else
                __l = dmax + 1;
        }
        dmax = __l - 1;
        // print adjust edges
        std::cout << "adjust dmax = " << dmax << " edges = " << __edges << std::endl;
        // print end
    }
}

int NGPowerLow::get_d() {
    if (d_index < drange) {
        if (d_number < simple_mf[d_index]) 
            d_number += 1;
        else {
            d_index += 1;
            d_number = 1;
        }
        return d_index + dmin;
    } else {
        return d_index + dmin - 1;
    }
}

double NGPowerLow::gen_uniform() {
    double res = std::max(distribution(generator), inj_cdf[0]);
    res = std::min(res, inj_cdf[drange]);
    return res;
}

inline int NGPowerLow::hash_function(double x) {
    return (int)(x * hash_factor);
}

void NGPowerLow::post_processing() {
    inj_cdf.resize(drange + 1);
    inj_idx.resize(drange + 1);
    inj_cdf[0] = 0.0;
    inj_idx[0] = -1;
    for (int i = 1; i <= drange; ++ i) {
        int __num = simple_mf[i - 1];
        inj_idx[i] = inj_idx[i - 1] + __num;
        inj_cdf[i] = inj_cdf[i - 1] + __num * (i - 1 + dmin);
    }
    inj_cdf[0] = dmin / inj_cdf[drange];
    inj_idx[0] = 0;
    inj_idx[drange] = nodes - 1;
    double min_cdf_step = 1.0;
    for (int i = 1; i <= drange; ++ i) {
        inj_cdf[i] /= inj_cdf[drange];
        min_cdf_step = std::min(min_cdf_step, inj_cdf[i] - inj_cdf[i - 1]);
    }
    // TODO 
    // inj_cdf[drange] = inj_cdf[drange - 1] + (1.0 - inj_cdf[drange - 1]) / 2.0;
    // min_cdf_step = std::min(min_cdf_step, inj_cdf[drange] - inj_cdf[drange - 1]);

    // build hash tables
    int digits = 0;
    double __temp = min_cdf_step;
    while (__temp < 1.0) {
        digits -= 1;
        __temp *= 10.0;
    }
    // print mid information
    std::cout << "min_cdf_step = " << min_cdf_step << " adjust_min_step = " << pow(10.0, digits * 1.0) << std::endl;
    // print end

    hash_factor = pow(10.0, -digits * 1.0);
    int ht_length = hash_factor + 3;
    std::vector<int> hash_index_next;
    std::vector<double> hash_cdf_next;
    hash_index.resize(ht_length);
    hash_index_next.resize(ht_length);
    hash_cdf.resize(ht_length);
    hash_cdf_next.resize(ht_length);
    hash_ratio.resize(ht_length);

    int __pre_v = 0, __pre_i = 0;
    for (int j = 1; j <= drange; ++ j) {
        int i = hash_function(inj_cdf[j]);
        for (int k = __pre_i; k < i; ++ k) {
            hash_index[k] = __pre_v;
            hash_index_next[k] = inj_idx[j];
            hash_cdf[k] = inj_cdf[j - 1];
            hash_cdf_next[k] = inj_cdf[j];
            if ((hash_cdf_next[k] - hash_cdf[k]) < 1e-8) 
                hash_ratio[k] = 0.0;
            else
                hash_ratio[k] = (hash_index_next[k] - hash_index[k]) / (hash_cdf_next[k] - hash_cdf[k]);
        }
        __pre_v = inj_idx[j];
        __pre_i = i;
    }
    for (int k = __pre_i; k < ht_length; ++ k) {
        hash_index[k] = __pre_v;
        hash_index_next[k] = nodes - 1;
        hash_cdf[k] = inj_cdf[drange];
        hash_cdf_next[k] = 1.0;
        if ((hash_cdf_next[k] - hash_cdf[k]) < 1e-8) 
            hash_ratio[k] = 0.0;
        else
            hash_ratio[k] = (hash_index_next[k] - hash_index[k]) / (hash_cdf_next[k] - hash_cdf[k]);
    }
}

int NGPowerLow::get_j() {
    double y = gen_uniform();
    int __i = hash_function(y);
    int a, ans;
    double c, r;
    if (y >= hash_cdf[__i]) {
        a = hash_index[__i];
        c = hash_cdf[__i];
        r = hash_ratio[__i];
    } else {
        a = hash_index[__i - 1];
        c = hash_cdf[__i - 1];
        r = hash_ratio[__i - 1];
    }
    ans = a + (y - c) * r;
    return ans;
}