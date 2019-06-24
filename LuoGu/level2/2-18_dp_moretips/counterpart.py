# -*- coding: utf-8 -*-
import os
import sys
import random 

error_data = 0
iterations = 0


def gen_data_1052(output):
    L_min, L_max = 1, 10000000
    ST_min, ST_max = 1, 10
    M_min, M_max = 1, 100
    with open(output, 'w') as fout:
        L = random.randint(L_min, L_max)
        S = random.randint(ST_min, ST_max)
        T = random.randint(S, ST_max)
        M = random.randint(M_min, min(M_max, L))
        all_positions = list(range(1, L))
        random.shuffle(all_positions)
        select_pos = all_positions[:M]
        fout.write(str(L) + '\n')
        fout.write(' '.join([str(S), str(T), str(M)]) + '\n')
        fout.write(' '.join([str(_) for _ in sorted(select_pos)]) + '\n')


def gen_data_1156(output):
    D_min, D_max = 2, 100
    G_min, G_max = 1, 100
    T_min, T_max = 0, 1000
    F_min, F_max = 1, 30
    H_min, H_max = 1, 25
    with open(output, 'w') as fout:
        D = random.randint(D_min, D_max)
        G = random.randint(G_min, G_max)
        fout.write('%d %d\n' % (D, G))
        for _ in range(G):
            T = random.randint(T_min, T_max)
            F = random.randint(F_min, F_max)
            H = random.randint(H_min, H_max)
            fout.write('%d %d %d\n' % (T, F, H))


def rename_data(output='data'):
    global error_data
    new_name = output + '_' + str(error_data)
    os.rename(output, new_name)
    error_data += 1


def process(proc0, proc1, output='data'):
    global iterations
    base_cmd = proc0 + ' < ' + output
    comp_cmd = proc1 + ' < ' + output
    gen_data(output)
    print('input [%d]: ' % (iterations))
    iterations += 1
    with open(output, 'r') as fin:
        print(fin.read())
    base_res = os.popen(base_cmd).read().strip()
    comp_res = os.popen(comp_cmd).read().strip()
    print('The result of baseline method: %s' % (base_res))
    print('The result of compared method: %s' % (comp_res))
    if base_res != comp_res:
        ch = input('continue [y]/n > ')
        if ch == 'n':
            print('exit ...')
            exit(0)
        else:
            rename_data()


def usage():
    print('current parameters: %s' % (' '.join(sys.argv)))
    print('Usage: python %s {baseline method} {compared method} {count}' % (os.path.basename(__file__)))
    exit(0)


def main():
    if len(sys.argv) != 4:
        usage()
    proc0 = sys.argv[1]        # baseline method
    proc1 = sys.argv[2]        # compared mehtod
    count = int(sys.argv[3])
    for _ in range(count):
        process(proc0, proc1)
    print('done. ')


if __name__ == '__main__':
    main()

