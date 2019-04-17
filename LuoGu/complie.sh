#!/bin/bash

if [ ! -f P$1.cpp ]; then
	echo P$1.cpp does not exist.
	exit 0
fi

echo $(date)
echo compling P$1.cpp ...
g++ -std=c++11 P$1.cpp -o main
echo done.

