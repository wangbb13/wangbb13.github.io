#!/bin/bash

name=$1
fn=$1.cpp

if [ -f $fn ]; then
	echo $fn exists.
	if [ $2 == 1 ]; then
		echo open $fn ...
		vim $fn
	fi
	exit 0
fi

touch $fn $name.in $name.out
echo create $fn files done. 

echo "/*" >> $fn
echo "ID: wangbb21" >> $fn 
echo "LANG: C++11" >> $fn
echo "TASK: $name" >> $fn
echo "*/" >> $fn
echo "#include <iostream>" >> $fn
echo "#include <fstream>" >> $fn
echo "using namespace std;" >> $fn
echo "" >> $fn
echo "int main() {" >> $fn
echo "    ofstream fout(\"$name.out\");" >> $fn
echo "    ifstream fin(\"$name.in\");" >> $fn
echo "    // " >> $fn
echo "    fin.close();" >> $fn
echo "    fout.close();" >> $fn
echo "    return 0;" >> $fn
echo "}" >> $fn
echo "" >> $fn

echo input template done. 

if [ $2 == 1 ]; then
	echo open $fn ...
	vim $fn
fi

