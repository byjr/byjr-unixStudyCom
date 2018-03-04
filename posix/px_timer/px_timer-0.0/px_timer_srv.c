#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "px_timer.c"
#include <lzl/cs_cmd.h>
#include <lzl/px_thread.h>
#include <lzl/px_sem.h>
typedef enum{
	IDX_MIN=-1,
	IDX_STAR,
	IDX_READ,
	IDX_WRITE,
	IDX_MAX,
}rw_idx_t;
pthread_t tida[]={0};
timer_t tm_id=0;
sem_t sema[]={
	[IDX_STAR	]={0},
};
typedef void *(*p_start_routine_t)(void *);
void *star_routine(void *args){
	struct timespec ts = {1,0};	
	do{
		nanosleep(&ts, NULL);	
		war("%s:%d/%ld is done",__func__,getpid(),pthread_self());		
	}while(0);
}
p_start_routine_t p_routine_array[]={
	&star_routine,
};
int aget_handle(void *args){
	int ret=0;
	if(ret)return -1;
	return 0;
}
int aset_handle(void *args){
	int ret=0;
	if(ret)return -1;
	return 0;
}
cs_cmd_t cs_cmd_tbl[]={
	ADD_CMD_ITEM(aget)
};
// struct timespec
  // {
    // __time_t tv_sec;		/* Seconds.  */
    // __syscall_slong_t tv_nsec;	/* Nanoseconds.  */
  // };
struct itimerspec itr = {0};	
void sig_callback(int sig_no){
	inf("sig_no=%d",sig_no);
	timer_gettime(tm_id,&itr);
	inf("itr:\n%ld\n%ld\n%ld\n%ld",
		itr.it_interval.tv_sec,
		itr.it_interval.tv_nsec,
		itr.it_value.tv_sec,
		itr.it_value.tv_nsec			
	);
}
int main(int argc,char **argv){
	int ret=0,i=0;
	log_init(NULL);
// tools_init_code begin:
	struct sigevent evp={
		.sigev_signo = SIGUSR1,
		.sigev_notify = SIGEV_SIGNAL,	
	};
	signal(SIGUSR1,sig_callback);
	px_timer_create(CLOCK_REALTIME,&evp,&tm_id);
	struct itimerspec it={{2,0},{1,0}};
	px_timer_set(tm_id,0,&it,0);
// tools_init_code end//
	cs_cmd_init(SIGRTMIN);
	int count=getCount(cs_cmd_tbl);
	do{
		cs_cmd_wait();
		cs_cmd_proc(cs_cmd_tbl,count,px_shm->cmd_buf);
	}while(1);
// tools_deinit_code:

	return 0;
}