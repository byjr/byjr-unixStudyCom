#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <slog/slog.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int main(int argc,char **argv)  
{
	int ret=0;
/* 	do{
		struct timespec ts={0};
		ret=clock_gettime(CLOCK_REALTIME, &ts);
		if(-1==ret){
			err("clock_gettime fail,errno:%d[%s].",errno,strerror(errno));
		}		
		ipt("----%d",ts.tv_sec);
		usleep(300*1000);
	}while(1); */
	return 0;
} 
