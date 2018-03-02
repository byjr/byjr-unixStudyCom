#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "px_spin.c"
#include <lzl/cs_cmd.h>
#include <lzl/px_thread.h>
#include <lzl/px_sem.h>
#include <pthread.h>
typedef enum{
	IDX_MIN=-1,
	IDX_STAR,
	IDX_READ,
	IDX_WRITE,
	IDX_MAX,
}rw_idx_t;
pthread_spinlock_t spin={0};
pthread_t tida[]={0,0,0};
sem_t sema[]={
	[IDX_STAR	]={0},
	[IDX_READ	]={0},
	[IDX_WRITE	]={0},
};
typedef void *(*p_start_routine_t)(void *);
volatile int global_res=0;
void *star_routine(void *args){
	struct timespec ts = {0,600000000};	
	do{
		px_spin_lock(&spin);
		nanosleep(&ts, NULL);
		inf("global_res:%d",global_res);
		px_spin_unlock(&spin);		
		// war("%s:%d/%ld is done",__func__,getpid(),pthread_self());		
	}while(1);
}
void *read_routine(void *args){
	struct timespec ts = {1,0};	
	do{
		// px_semwait(&sema[IDX_READ]);
		px_spin_lock(&spin);
		nanosleep(&ts, NULL);
		global_res--;
		px_spin_unlock(&spin);		
		war("%s:%d/%ld is done",__func__,getpid(),pthread_self());		
	}while(1);	
}
void *write_routine(void *args){
	struct timespec ts = {1,0};	
	do{
		// px_semwait(&sema[IDX_WRITE]);
		px_spin_lock(&spin);
		nanosleep(&ts, NULL);
		global_res++;
		px_spin_unlock(&spin);		
		inf("%s:%d/%ld is done",__func__,getpid(),pthread_self());		
	}while(1);	
}
p_start_routine_t p_routine_array[]={
	&star_routine,
	&read_routine,
	&write_routine,
};
int star_handle(void *args){
	int ret=0;
	// px_thread_create(&tida[IDX_STAR],NULL,p_routine_array[IDX_STAR],NULL);
	if(ret)return -1;
	return 0;
}
int read_handle(void *args){
	int ret=0;
	// px_thread_create(&tida[IDX_READ],NULL,p_routine_array[IDX_READ],NULL);
	if(ret)return -1;
	return 0;
}
int write_handle(void *args){
	int ret=0;
	// px_thread_create(&tida[IDX_WRITE],NULL,p_routine_array[IDX_WRITE],NULL);
	if(ret)return -1;
	return 0;
}
cs_cmd_t cs_cmd_tbl[]={
	ADD_CMD_ITEM(star)	
	ADD_CMD_ITEM(read)
	ADD_CMD_ITEM(write)
};

int main(int argc,char **argv){
	int ret=0,i=0;
	log_init(NULL);
// tools_init_code begin:
	px_spin_init(&spin,PTHREAD_PROCESS_SHARED);
	for(i=0;i<getArrayCount(tida);i++){
		px_thread_create(&tida[i],NULL,p_routine_array[i],NULL);
		// px_seminit(&sema[i],0,0);
	}
// tools_init_code end://
	cs_cmd_init(SIGRTMIN);
	int count=sizeof(cs_cmd_tbl)/sizeof(cs_cmd_tbl[0]);
	do{
		cs_cmd_wait();
		cs_cmd_proc(cs_cmd_tbl,count,px_shm->cmd_buf);
	}while(1);
// tools_deinit_code:

	for(i=0;i<getArrayCount(tida);i++){
		// px_semdestroy(&sema[i]);		
		px_thread_join(tida[i],NULL);
	}
	px_spin_destroy(&spin);
	return 0;
}