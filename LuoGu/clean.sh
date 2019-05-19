#!/bin/bash

if [ ! -d $1 ]; then
	echo "$1 is not a directory"
	exit 1
fi

for file in $(find $1 -type f); do
	name=${file##*/}
	if [ "$name" == "main.exe" ]; then
		echo "rm $file"
		rm $file
	fi
done

