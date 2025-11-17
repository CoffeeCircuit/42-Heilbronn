#!/bin/bash

shuf -i 0-9999 -n $1 > args.txt ; ./push_swap --bench --simple $(cat args.txt)
rm ./args.txt
