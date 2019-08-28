#!/bin/bash 

for file in $(ls *.json); do 
echo replace in $file
sed -i 's/vss/node/g' $file
sed -i 's/ess/edge/g' $file
sed -i 's/edges/amount/g' $file
done

