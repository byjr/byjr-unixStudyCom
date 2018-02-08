#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <lzl/misc.h>
#include <lzl/px_thread.h>
#include <lzl/slog.h>


int main(int argc,char **argv){
	int ret=0,i=0;
	unsigned long long count=0;
	do{
		exec_cmd2("/tmp/threadpool-0.0/threadpool_tt2");
	}while(--count);
	return 0;
}