#!/bin/sh
fifo=/tmp/$1.fifo
var=$*
if [ ! -p $pipe ]; then
	exit 1
else
	echo $2 > $fifo
fi
