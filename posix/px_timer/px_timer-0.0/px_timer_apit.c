#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "px_timer.c"
#include <lzl/cs_cmd.h>
#include <lzl/px_thread.h>
#include <lzl/px_sem.h>
int cid_a[]={
	CLOCK_REALTIME,
	CLOCK_MONOTONIC ,
	CLOCK_MONOTONIC_RAW ,
	CLOCK_PROCESS_CPUTIME_ID,
	CLOCK_THREAD_CPUTIME_ID,
};
int main(int argc,char **argv){
	int ret=0,i=0;
	log_init(NULL);
	struct timespec t2={0},t1={0},tv={0};
	do{
		for(i=0;i<get_ar_count(cid_a);i++){
			
		}
		ret=clock_getres(CLOCK_REALTIME,&t1);
	}while(1);

	return 0;
}