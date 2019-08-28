#!/bin/bash
#sng

echo 
echo $(date)

java Generator 1.15 1 1000 1.15 1 1000 100000 3200000 a_exp1.adj


python3 degree_calculation.py

python3 heat.py 100000 100000 a_exp1.adj a_comm2.txt

python2 twsnap.py a_exp1.adj -1 1 0 0 0 


echo
echo $(date)

