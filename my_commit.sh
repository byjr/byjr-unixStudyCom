#!/bin/sh
cd /home/lz/work/w-rt-study/byjr-unixStudyCom/
is_wait=$1
commitM=""
git status

if [ x$is_wait = "x" ]; then
	echo -n "\033[33;1mPlease input commit masseg :\033[0m"
	read commitM
else
	commitM=$2
fi
git add -A .
git commit -m "$commitM"

if [ x$is_wait = "x" ]; then
	echo -n "\033[33;1mAre you want to push :\033[0m"
	read yn_store
fi
git push origin master
cd -
