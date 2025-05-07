#!/bin/bash

if [ $# -eq 0 ]; then
	echo "usage : $0 \"your sentence here\""
	exit 1
fi

sentence="$*"

vowel_count=$(echo "$sentence" | grep -o -i '[aeiou]' | wc -l)

echo "number of vowels: $vowel_count"
