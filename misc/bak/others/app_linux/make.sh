input=$1
make TAGERTS=$input clean && make TAGERTS=$input ./$input
