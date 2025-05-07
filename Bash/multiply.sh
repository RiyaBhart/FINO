#!/bin/bash

if [ $# -ne 2 ]; then
	echo "usage : $0 <num1> <num2>"
	exit 1
fi

result=$(( $1 * $2 ))

echo "result: $result"
