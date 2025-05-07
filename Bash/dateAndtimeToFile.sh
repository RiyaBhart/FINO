#!/bin/bash

if [ -z "$1" ]; then
	echo "usage: $0 <filename>"
	exit 1
fi

filename="$1"

if [ -f "$filename" ];then
	echo "$(date)" >> "filename"
	echo "date and time appended to $filename."
else
	echo "error: file '$filename' not found!"
	exit 1
fi
