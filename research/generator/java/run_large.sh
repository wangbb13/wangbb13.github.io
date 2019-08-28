#!/bin/bash

# java Generator 1.15 1 30 1.15 1 20 10 100 tmp.adj

# java -Xmx8g  Generator 1.15 1 100000 1.15 1 200000 67108864 1000000000 tmp.adj  
# java -Xmx8g  Generator 1.15 1 100000 1.15 1 200000 67108864 1000000000 tmp.adj  


# 2^30 10^12
# java -Xmx8g  MultiThreadGenerator 1.15 1 10000 1.15 1 20000 16777216 1000000000 tmp.adj 100 

# 2^26 10^9
# java -Xmx8g  MultiThreadGenerator 1.15 1 100000 1.15 1 200000 67108864 1000000000 tmp.adj 100 

for i in 1 2 3 4 5 
do
java -Xmx8g  Generator 1.15 1 100000 1.15 1 200000 33554432 1000000000 L25.adj
done

for i in 1 2 3 4 5 
do
java -Xmx8g  Generator 1.15 1 100000 1.15 1 200000 67108864 10000000000 L26.adj
done

for i in 1 2 3 4 5 
do
java -Xmx8g  Generator 1.15 1 100000 1.15 1 200000 134217728 10000000000 L27.adj
done

for i in 1 2 3 4 5 
do
java -Xmx8g  Generator 1.15 1 100000 1.15 1 200000 268435456 10000000000 L28.adj
done

for i in 1 2 3 4 5 
do
java -Xmx8g  Generator 1.15 1 100000 1.15 1 200000 536870912 100000000000 L29.adj
done

for i in 1 2 3 4 5 
do
java -Xmx8g  Generator 1.15 1 100000 1.15 1 200000 1073741824 1000000000000 L30.adj
done
