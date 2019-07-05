#!/bin/bash

if [ ! -f $1.cpp ]; then
	echo $1.cpp does not exist.
	exit 0
fi

echo $(date)
echo compling $1.cpp ...
g++ -std=c++11 $1.cpp -o main
echo done.

