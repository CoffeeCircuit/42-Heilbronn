#!/bin/bash
for i in $(seq 2 500); do
    seq -9999 9999 | shuf -n $i > args.txt
    echo -n "test $i numbers: "
    args=$(cat args.txt)
    res=$(./push_swap --simple $args | ./checker_linux $args)
    if [ "$res" != "OK" ]; then
        break
    fi
	echo "$res"
done
