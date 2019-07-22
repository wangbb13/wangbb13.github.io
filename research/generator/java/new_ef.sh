#!/bin/bash

echo >> new_ef.txt
echo >> new_ef.txt
echo $(date) >> new_ef.txt
echo >> new_ef.txt
echo >> new_ef.txt

for i in 1 2 3 4 5 
do
  java Generator 1.15 1 80 1.15 1 80 131072 2097152 ef1726.adj >> new_ef.txt
done


for i in 1 2 3 4 5 
do
  java Generator 1.15 1 80 1.15 1 80 262144 4194304 ef1726.adj >> new_ef.txt
done


for i in 1 2 3 4 5 
do
  java Generator 1.15 1 80 1.15 1 80 524288 8388608 ef1726.adj >> new_ef.txt
done


for i in 1 2 3 4 5 
do
  java Generator 1.15 1 80 1.15 1 80 1048576 16777216 ef1726.adj >> new_ef.txt
done


for i in 1 2 3 4 5 
do
  java Generator 1.15 1 80 1.15 1 80 2097152 33554432 ef1726.adj >> new_ef.txt
done


for i in 1 2 3 4 5 
do
  java Generator 1.15 1 80 1.15 1 80 4194304 67108864 ef1726.adj >> new_ef.txt
done


for i in 1 2 3 4 5 
do
  java Generator 1.15 1 80 1.15 1 80 8388608 134217728 ef1726.adj >> new_ef.txt
done


for i in 1 2 3 4 5 
do
  java Generator 1.15 1 80 1.15 1 80 16777216 268435456 ef1726.adj >> new_ef.txt
done


for i in 1 2 3 4 5 
do
  java Generator 1.15 1 80 1.15 1 80 33554432 536870912 ef1726.adj >> new_ef.txt
done


for i in 1 2 3 4 5 
do
  java Generator 1.15 1 80 1.15 1 80 67108864 1073741824 ef1726.adj >> new_ef.txt
done

