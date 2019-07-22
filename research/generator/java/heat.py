# -*- coding: utf-8 -*-
# just for adj format
# Input: row col input_file output_file
import os
import sys
import math


def adj_to_heat(mxn, mxm, i_file, o_file, nm=100):
    td_array = [[0 for _ in range(nm)] for _ in range(nm)]
    row_step = int(mxn / nm)
    col_step = int(mxm / nm)
    cell_max_val = 0
    with open(i_file, 'r') as fin:
        for line in fin:
            line = line.strip().split()
            if len(line) > 0:
                row = int(line[0])
                t_row = min(int(row / row_step), nm - 1)
                for c in line[1:]:
                    col_i = int(c)
                    t_col = min(int(col_i / col_step), nm - 1)
                    td_array[t_row][t_col] += 1
                    cell_max_val = max(cell_max_val, td_array[t_row][t_col])
    # trick
    further_stat = [0 for _ in range(cell_max_val + 1)]
    gz = 0
    for i in range(nm):
        for j in range(nm):
            further_stat[td_array[i][j]] += 1
            if td_array[i][j] > 0:
                gz += 1
    hyper, hyper2 = 40, 50
    tmp, tmp_i = 0, 100
    threshold = int(gz / hyper)
    further_func = [100 - hyper for _ in range(cell_max_val + 1)]
    for i in range(cell_max_val, -1, -1):
        further_func[i] = tmp_i
        tmp += further_stat[i]
        if (tmp_i > (100 - hyper)) and tmp > threshold:
            tmp = 0
            tmp_i -= 1
    further_func[0] = hyper2
    for i in range(nm):
        for j in range(nm):
            td_array[i][j] = further_func[td_array[i][j]]
    with open(o_file, 'w') as fout:
        for i in range(nm - 1, -1, -1):
            line = ' '.join([str(td_array[i][_]) for _ in range(nm)]) + '\n'
            fout.write(line)


def main():
    a = int(sys.argv[1])
    b = int(sys.argv[2])
    c = sys.argv[3]
    d = sys.argv[4]
    adj_to_heat(a, b, c, d)


if __name__ == '__main__':
    main()
