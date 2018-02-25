#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "px_rwlock.c"
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
pthread_rwlockattr_t rwlockattr={0};
pthread_rwlock_t rwlock={0};
pthread_t tida[]={0,0,0};
sem_t sema[]={
	[IDX_STAR	]={0},
	[IDX_READ	]={0},
	[IDX_WRITE	]={0},
};
typedef void *(*p_start_routine_t)(void *);
void *star_routine(void *args){
	struct timespec ts = {1,0};	
	do{
		px_rwlock_wrlock(&rwlock);
		nanosleep(&ts, NULL);
		px_rwlock_unlock(&rwlock);		
		war("%s:%d/%ld is done",__func__,getpid(),pthread_self());		
	}while(0);
}
void *read_routine(void *args){
	struct timespec ts = {1,0};	
	do{
		// px_semwait(&sema[IDX_READ]);
		px_rwlock_rdlock(&rwlock);
		nanosleep(&ts, NULL);
		px_rwlock_unlock(&rwlock);		
		war("%s:%d/%ld is done",__func__,getpid(),pthread_self());		
	}while(0);	
}
void *write_routine(void *args){
	struct timespec ts = {5,0};	
	do{
		// px_semwait(&sema[IDX_WRITE]);
		px_rwlock_wrlock(&rwlock);
		nanosleep(&ts, NULL);
		px_rwlock_unlock(&rwlock);		
		inf("%s:%d/%ld is done",__func__,getpid(),pthread_self());		
	}while(0);	
}
p_start_routine_t p_routine_array[]={
	&star_routine,
	&read_routine,
	&write_routine,
};
int aget_handle(void *args){
	int ret=0;
	ret=px_rwlockattr_show(&rwlockattr);
	if(ret)return -1;
	return 0;
}
int aset_handle(void *args){
	int ret=0;
	ret=px_rwlockattr_set(&rwlockattr);
	if(ret)return -1;
	return 0;
}
int star_handle(void *args){
	int ret=0;
	px_thread_create(&tida[IDX_STAR],NULL,p_routine_array[IDX_STAR],NULL);
	if(ret)return -1;
	return 0;
}
int read_handle(void *args){
	int ret=0;
	px_thread_create(&tida[IDX_READ],NULL,p_routine_array[IDX_READ],NULL);
	if(ret)return -1;
	return 0;
}
int write_handle(void *args){
	int ret=0;
	px_thread_create(&tida[IDX_WRITE],NULL,p_routine_array[IDX_WRITE],NULL);
	if(ret)return -1;
	return 0;
}
cs_cmd_t cs_cmd_tbl[]={
	ADD_CMD_ITEM(aget)
	ADD_CMD_ITEM(aset)
	ADD_CMD_ITEM(star)	
	ADD_CMD_ITEM(read)
	ADD_CMD_ITEM(write)
};

int main(int argc,char **argv){
	int ret=0,i=0;
	log_init(NULL);
// tools_init_code begin:
	px_rwlockattr_init(&rwlockattr);
	px_rwlock_init(&rwlock,&rwlockattr);
	for(i=0;i<get_ar_count(tida);i++){
		// px_thread_create(&tida[i],NULL,p_routine_array[i],NULL);
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

	for(i=0;i<get_ar_count(tida);i++){
		// px_semdestroy(&sema[i]);		
		// px_thread_join(tida[i],NULL);
	}
	px_rwlock_destroy(&rwlock);
	px_rwlockattr_destroy(&rwlockattr);
	return 0;
}