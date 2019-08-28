#!/bin/bash

# java Generator 1.15 1 30 1.15 1 20 33554432 1000000000 tmp.adj


java GenWithComm 1.15 1 30 1.15 1 20 10000 100000 comm1.adj 3 1.15 1.1 

java GenWithComm 1.15 1 30 1.15 1 20 10000 100000 comm2.adj 3 1.15 1.3 

java GenWithComm 1.15 1 30 1.15 1 20 10000 100000 comm3.adj 3 1.15 1.5 

java GenWithComm 1.15 1 30 1.15 1 20 10000 100000 comm4.adj 3 1.15 1.7 

java GenWithComm 1.15 1 30 1.15 1 20 10000 100000 comm5.adj 3 1.15 1.9 



java GenWithComm 1.15 1 30 1.15 1 20 10000 100000 comm51.adj 5 1.15 1.1 

java GenWithComm 1.15 1 30 1.15 1 20 10000 100000 comm52.adj 5 1.15 1.3 

java GenWithComm 1.15 1 30 1.15 1 20 10000 100000 comm53.adj 5 1.15 1.5 

java GenWithComm 1.15 1 30 1.15 1 20 10000 100000 comm54.adj 5 1.15 1.7 

java GenWithComm 1.15 1 30 1.15 1 20 10000 100000 comm55.adj 5 1.15 1.9 



mv comm*.adj ./comm

# java MultiThreadGenerator 1.15 1 30 1.15 1 20 33554432 1000000000 tmp.adj 10

