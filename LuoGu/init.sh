#!/bin/bash

fn=P$1.cpp

if [ -f $fn ]; then
	echo $fn exists.
	if [ $2 == 1 ]; then
		echo open $fn ...
		vim $fn
	fi
	exit 0
fi

touch $fn
echo create $fn done. 

echo "/**" >> $fn
echo " * Description: " >> $fn 
echo " * Input : " >> $fn
echo " * Output: " >> $fn
echo " * Time/Space Limit: 1s/128MB" >> $fn
echo " */" >> $fn
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

