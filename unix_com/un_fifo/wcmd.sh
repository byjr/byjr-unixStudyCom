pipe="/tmp/cmd.fifo"
if [ ! -p $pipe ]; then
	exit 1
else
	echo "$*" > $pipe
fi
