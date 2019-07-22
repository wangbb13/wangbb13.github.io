#!/bin/bash


if [ -f "data.adj" ]; then
rm data*.adj new_data_*.adj
fi

echo 
echo 
echo $(date)
echo =======================================================================


# java Streaming 1.15 1 80 1.15 1 80 100000 2000000 data.adj 0.1 
java Streaming 1.15 1 80 1.15 1 80 10000 600000 data.adj 0.1 

python3 refine.py

echo ===================== generation end ==================================

