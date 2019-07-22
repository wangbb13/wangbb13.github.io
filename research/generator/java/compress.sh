#!/bin/bash 

files="community0 community1 community2 community3 simple0 simple1 simple2 simple3"

for file in $files; do
echo "compress graph [ $file ] ... "
tar -zcvf $file.tar.gz $file 
done 

