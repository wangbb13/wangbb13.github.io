#!/bin/bash
#sng

echo 
echo $(date)

java Generator 1.15 1 1000 1.15 1 1000 1000000 300000000 1M.adj


# python3 degree_calculation.py

# python3 heat.py 100000 100000 exp1.adj comm2.txt

python2 twsnap.py exp1.adj -1 1 0 0 0 


java Generator 1.15 1 1000 1.15 1 1000 10000000 3000000000 1M.adj
python2 twsnap.py exp1.adj -1 1 0 0 0 


echo
echo $(date)

