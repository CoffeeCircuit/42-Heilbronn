#!/bin/bash
args=args.txt
ops=ops.txt

seq -9999 9999 | shuf -n $1 | tr "\n" " " > $args
./push_swap "$(cat $args)" > $ops
echo -n "Ops: "
wc -l $ops | awk '{print $1}'
cat $ops | ./checker_linux $(cat args.txt)

