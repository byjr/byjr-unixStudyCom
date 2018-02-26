#include <signal.h>
#include <stdlib.h>
#include "px_timer.c"
#include "lzl/px_thread.h"
#include "lzl/px_shm.h"
#include "lzl/fifo_cmd.h"
#include "lzl/misc.h"
#define CID CLOCK_MONOTONIC
int main(int argc,char *argv[]){
	log_init("l=11111");
	int cid=0;
	int ret=clock_getcpuclockid(getpid(), &cid);
	if(ret<0){
		err("");
		return -1;
	}	
	struct timespec ts1={0};
	struct timespec ts2={0};
	do{
		px_gettime(CID,&ts1);
		usleep(500000);
		px_gettime(CID,&ts2);
		long tsd=get_tsd(&ts2,&ts1,'n');
		dbg("tsd=%3d",tsd);
		mt_start(CID);
		usleep(500000);		
		dbg("tsd=%3d",mt_get(CID));
	}while(0);
	return 0;
}
