#!/bin/bash

if [ -f "tmp.adj" ]; then
rm tmp.adj tmp_*.adj
fi

java Generator 1.15 1 80 1.15 1 80 67108864 1073741824 tmp.adj 


# java Streaming 1.15 1 80 1.15 1 80 10000 600000 tmp.adj 0.1


# java Streaming 1.15 1 80 1.15 1 80 5000 200000 tmp.adj 1.0


