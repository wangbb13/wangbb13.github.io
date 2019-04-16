#!/bin/bash

fn=P$1.cpp

if [ -f $fn ]; then
	echo $fn exists.
	exit 0
fi

touch $fn
echo create $fn done. 

echo "#include <iostream>" >> $fn
echo "using namespace std;" >> $fn
echo "" >> $fn
echo "int main() {" >> $fn
echo "    // " >> $fn
echo "    return 0;" >> $fn
echo "}" >> $fn
echo "" >> $fn

echo input template done. 

if [ $2 == 1 ]; then
	echo open $fn ...
	vim $fn
fi

