#!/bin/sh
srcN=$1
dstN=$2
find -type d | xargs  rename "s/"$srcN"/"$dstN"/g"
find -name *.[ch] | xargs  rename "s/"$srcN"/"$dstN"/g"
find -name *.[ch] | xargs perl -p -i -e "s/"$srcN"/"$dstN"/g"
echo replace $srcN to $dstN complete!


