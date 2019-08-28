# -*- coding: utf-8 -*-
import os
import sys


def stats(filename):
    print(filename)
    if not os.path.exists(filename):
        print(filename, 'does not exist.')
        exit(0)
    # src_map = dict()
    # tgt_map = dict()
    # src_nid, tgt_nid = 0, 0
    uni_map = dict()
    uni_nid = 0
    n_edges = 0
    with open(filename, 'r') as fin:
        for line in fin:
            line = line.split()
            if len(line) > 0:
                n_edges += len(line) - 1
                for no in line:
                    if no not in uni_map:
                        uni_map[no] = str(uni_nid)
                        uni_nid += 1
    '''
    new_file = 'new_' + filename
    fout = open(new_file, 'w')
    with open(filename, 'r') as fin:
        for line in fin:
            line = line.split()
            if len(line) > 0:
                row = ' '.join([uni_map[_] for _ in line]) + '\n'
                fout.write(row)
    fout.close()
    '''
    print('nodes:', uni_nid)
    print('edges:', n_edges)
    print('done.')


def main():
    file_list = ['data_0.adj', 'data_1.adj', 'data_2.adj', 'data_3.adj', 'data_4.adj', 'data_5.adj', 'data_6.adj', 'data_7.adj', 'data_8.adj', 'data_9.adj']
    for file in file_list:
        stats(file)
    # stats(sys.argv[1])


if __name__ == '__main__':
    main()
