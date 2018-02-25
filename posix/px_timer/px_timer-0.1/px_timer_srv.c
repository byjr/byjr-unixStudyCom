#include <signal.h>
#include <stdlib.h>
#include "px_timer.c"
#include "lzl/px_thread.h"
#include "lzl/px_shm.h"
#include "lzl/fifo_cmd.h"
#include "lzl/misc.h"
timer_t tmID={0};
int start_handle(void *args){
	struct itimerspec it={{2,0},{1,500000000}};
	char ** argv=(char **)args;
	do{
		int ret=px_timer_set(tmID,0,&it,NULL);
		if(ret<0)return -1;
		war("%s:%d is succeed!",__func__,getpid());
	}while(0);
	return 0;
}
fifo_cmd_t fifo_cmd_tbl[]={
	ADD_CMD_ITEM(start)
};
// void func_waitpid(int signo) {
    // pid_t pid;
    // int stat;
    // while( (pid = waitpid(-1, &stat, WNOHANG)) > 0 ) {
        // inf_nl( "child %d exit", pid );
    // }
    // return;
// }
void timer_handle(int sig){
	dbg_nl(__func__);
	// struct itimerspec it={0};
	// px_timer_set(tmID,0,&it,NULL);
}
void *start_routine(void *args){
	struct timespec tsv={0,200000000};
	struct itimerspec it={0};
	do{
		nanosleep(&tsv,NULL);
		int ret=px_timer_get(tmID,&it);
		if(ret<0)continue;
		inf("it_interval:%2u.%09u",it.it_interval.tv_sec,it.it_interval.tv_nsec);
		inf("it_value   :%2u.%09u",it.it_value.tv_sec,it.it_value.tv_nsec);
		inf("overrun:%d",px_timer_getoverrun(tmID));
	}while(1);
}
char *tid_tbl[]={
	"CLOCK_REALTIME",
	"CLOCK_MONOTONIC",
	"CLOCK_PROCESS_CPUTIME_ID",
	"CLOCK_THREAD_CPUTIME_ID",
	"CLOCK_MONOTONIC_RAW",
	"CLOCK_REALTIME_COARSE",
	"CLOCK_MONOTONIC_COARSE",
	"CLOCK_BOOTTIME",
	"CLOCK_REALTIME_ALARM",
	"CLOCK_BOOTTIME_ALARM",
	// "CLOCK_SGI_CYCLE",
	"CLOCK_TAI",
};
clockid_t tid_array[]={
	CLOCK_REALTIME,
	CLOCK_MONOTONIC,
	CLOCK_PROCESS_CPUTIME_ID,
	CLOCK_THREAD_CPUTIME_ID,
	CLOCK_MONOTONIC_RAW,
	CLOCK_REALTIME_COARSE,
	CLOCK_MONOTONIC_COARSE,
	CLOCK_BOOTTIME,
	CLOCK_REALTIME_ALARM,
	CLOCK_BOOTTIME_ALARM,
	// CLOCK_SGI_CYCLE,
	CLOCK_TAI,	
};
int get_timer(void *args){
	struct timespec tst={0,0};
	struct timespec ts={0,1000000000*0.2};
	char ** argv=(char **)args;
	int i=0;
	for(i=0;i<get_ar_count(tid_array);i++){		
		inf("%24s:%2u",tid_tbl[i],tid_array[i]);
		memset(&tst,0,sizeof(tst));
		int ret=clock_gettime(tid_array[i],&tst);
		if(ret<0)return -1;
		inf("-----------------------tst:%10u.%09u",tst.tv_sec,tst.tv_nsec);		
	}
	nanosleep(&ts,NULL);
	return 0;
}
int tools_init(void *args){
	// signal(SIGCHLD,func_waitpid);
	struct sigevent sev;
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_notify = SIGEV_SIGNAL;
	signal(SIGRTMIN,timer_handle);
	int ret=px_timer_create(CLOCK_MONOTONIC,&sev,&tmID);
	if(ret<0)return -1;
	pthread_t pxtid={0};
	ret=px_thread_create(&pxtid,NULL,start_routine,NULL);
	if(ret<0)return -1;
	return 0;
}
int main(int argc,char *argv[]){
	log_init("l=11111");
	int ret=tools_init(NULL);
	if(ret<0) return -1;
	pid_t pid=fork();
	if(pid<0)return -1;
	if(pid==0){
		// int ret=clock_getcpuclockid(getpid(), &tid_array[2]);
		// if(ret<0){
			// err("");
			// return -1;
		// }
		// ret=pthread_getcpuclockid(pthread_self(),&tid_array[3]);
		// if(ret<0){
			// err("");
			// return -1;
		// }		
		do{
			pause();
			// get_timer(NULL);
		}while(1);
	}
	ret=fifo_cmd_init("/tmp/cmd.fifo");
	if(ret<0)return -1;
	war("%s:%d is succeed!",__func__,getpid());
	do{
		fifo_cmd_wait();
		fifo_cmd_proc(fifo_cmd_tbl,get_ar_count(fifo_cmd_tbl));
	}while(1);
}