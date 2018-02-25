#include <signal.h>
#include <stdlib.h>
#include "px_timer.c"
#include "lzl/px_shm.h"
#include "lzl/fifo_cmd.h"
#include "lzl/misc.h"
timer_t tmID={0};
struct sigevent sev;
int rlock_handle(void *args){
	struct itimerspec it={{3,0},{1,500000000}};
	char ** argv=(char **)args;
	do{
		int ret=px_timer_set(tmID,0,&it,NULL);
		if(ret<0)return -1;
		war("%s:%d is succeed!",__func__,getpid());
	}while(0);
	return 0;
}
fifo_cmd_t fifo_cmd_tbl[]={
	ADD_CMD_ITEM(rlock)
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
}
int tools_init(void *args){
	// signal(SIGCHLD,func_waitpid);
	sev.sigev_signo = SIGRTMIN;
	sev.sigev_notify = SIGEV_SIGNAL;
	signal(SIGRTMIN,timer_handle);
	int ret=px_timer_create(CLOCK_MONOTONIC,&sev,&tmID);
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
		while(1)pause();
	}
	ret=fifo_cmd_init("/tmp/cmd.fifo");
	if(ret<0)return -1;
	war("%s:%d is succeed!",__func__,getpid());
	do{
		fifo_cmd_wait();
		fifo_cmd_proc(fifo_cmd_tbl,get_ar_count(fifo_cmd_tbl));				
	}while(1);
}