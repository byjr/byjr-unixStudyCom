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
	char buf[100]="";
	do{
		printf("%d\n",getpid());
		snprintf(buf,sizeof(buf),"%d\n",getpid());
		write_str_to_file("/tmp/show_pid.t",buf,"a");
	}while(0);
	return 0;
}