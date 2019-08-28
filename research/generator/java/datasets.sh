#!/bin/bash

path=./jsons

for file in $(ls $path); do 
echo $path/$file
# head -2 $path/$file
java Main $path/$file
done

