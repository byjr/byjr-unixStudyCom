#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <lzl/slog.h>
#include <lzl/misc.h>

void sig_handle(int n){
	inf("sig num is:%d",n);
}
typedef sig_handle
int 
main(int argc, char *argv[])
{
	int i=0,ret=0;
	log_init(NULL);
	for(i=SIGRTMIN;i<=SIGRTMAX;i++){
		if(signal(i,sig_handle)==SIG_ERR){
			show_errno(0,"signal");
			exit(-1);			
		}
	}
	while(1);
	return 0;
}