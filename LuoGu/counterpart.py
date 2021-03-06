# -*- coding: utf-8 -*-
import os
import sys
import random 

error_data = 0
iterations = 0


def gen_data(output):
    pass


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

