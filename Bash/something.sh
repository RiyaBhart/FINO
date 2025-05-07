#!/bin/bash

if [ -z "$1" ]; then
	echo "usage: $0 <file_or_directory_path>"
	exit 1
fi

path="$1"

if [ -e "$path" ]; then
	if [ -f "$path" ]; then
		echo "'$path' is a file."
	elif [ -d "$path" ];then
		echo"'$path' is a directory."
	else
		echo "'$path' exits but is neither a regular file nor a directory"
	fi
else
	echo"error: '$path' does not exist!"
fi

