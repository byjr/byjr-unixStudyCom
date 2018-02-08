#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "px_cond.c"
#include <lzl/cs_cmd.h>
#include <lzl/px_thread.h>
#include <lzl/px_sem.h>
#include <lzl/px_mutex.h>
typedef enum{
	IDX_MIN=-1,
	IDX_WAIT	,
	IDX_WAITD	,	
	IDX_SIGNAL	,
	IDX_BDCT	,
	IDX_MAX,
}rw_idx_t;
pthread_condattr_t condattr={0};
pthread_cond_t cond={0};
pthread_mutex_t mutex={0};

sem_t sema[]={
	[IDX_WAIT	]={0},
	[IDX_WAITD	]={0},	
	[IDX_SIGNAL	]={0},
	[IDX_BDCT	]={0},
};
typedef void *(*p_routine_t)(void *);
void *wait_routine(void *args){
	struct timespec ts = {1,0};
	do{
		// war("%s:%d/%ld is start",__func__,getpid(),pthread_self());		
		px_semwait(&sema[IDX_WAIT]);
		war("IDX_WAIT lock!");
		px_mutex_lock(&mutex);
		war("IDX_WAIT wait!");
		px_cond_wait(&cond,&mutex);
		war("IDX_WAIT unlock!");
		px_mutex_unlock(&mutex);
		dbg("IDX_WAIT done!");
		// nanosleep(&ts, NULL);
	}while(1);
}
void *tdwait_routine(void *args){
	struct timespec tv;
	struct timespec ts = {1,0};
	struct timespec nts = {1,0};
	do{
		// war("%s:%d/%ld is start",__func__,getpid(),pthread_self());		
		px_semwait(&sema[IDX_WAITD]);
		clock_gettime(CLOCK_MONOTONIC,&tv);
		tv.tv_sec+=20;	
		war("IDX_TDWAIT lock!");
		px_mutex_lock(&mutex);
		war("IDX_WAITD wait!");		
		px_cond_tdwait(&cond,&mutex,&tv);
		war("IDX_WAIT unlock!");		
		px_mutex_unlock(&mutex);
		dbg("IDX_WAITD done!");
		// nanosleep(&nts, NULL);		
	}while(1);
}
void *signal_routine(void *args){
	struct timespec ts = {1,0};
	do{
		// war("%s:%d/%ld is start",__func__,getpid(),pthread_self());		
		px_semwait(&sema[IDX_SIGNAL]);
		war("IDX_SIGNAL start!");
		px_mutex_lock(&mutex);
		px_cond_signal(&cond);
		px_mutex_unlock(&mutex);
		war("IDX_SIGNAL done!");
	}while(1);
}
void *broadcast_routine(void *args){
	struct timespec ts = {1,0};
	do{
		// war("%s:%d/%ld is start",__func__,getpid(),pthread_self());		
		px_semwait(&sema[IDX_BDCT]);
		war("IDX_BDCT start!");
		px_mutex_lock(&mutex);
		px_cond_broadcast(&cond);
		px_mutex_unlock(&mutex);
		war("IDX_BDCT done!");
	}while(1);
}
void *monitor_routine(void *args){
	struct timespec ts = {1,0};
	do{
		int i=0,ret=0;
		for(i=0;i<get_ar_count(sema);i++){
			int semv=0;
			ret=px_semgetvalue(&semv,&sema[i]);
			if(!ret)printf("sema[%d]=%d\n",i,semv);			
		}
		nanosleep(&ts,NULL);
	}while(1);	
}
p_routine_t p_routine_array[]={
	&wait_routine,
	&tdwait_routine,	
	&signal_routine,
	&broadcast_routine,
	// &monitor_routine,
};
pthread_t tida[get_ar_count(p_routine_array)]={0};
int aget_handle(void *args){
	int ret=0;
	ret=px_condattr_show(&condattr);
	if(ret)return -1;
	return 0;
}
int aset_handle(void *args){
	int ret=0;
	ret=px_condattr_set(&condattr);
	// ret=px_condattr_show(&condattr);
	if(ret)return -1;
	return 0;
}
int ctrl_handle(void *args){
	int ret=0,idx=0;
	char **argv=(char **)args;
	if(!argv[2])return -1;
	idx=atoi(argv[2]);
	inf("%d",idx);
	ret=px_sempost(&sema[idx],1);
	if(ret)return -1;
	return 0;
}
cs_cmd_t cs_cmd_tbl[]={
	ADD_CMD_ITEM(aget)
	ADD_CMD_ITEM(aset)
	ADD_CMD_ITEM(ctrl)
};
int main(int argc,char **argv){
	int ret=0,i=0;
	log_init(NULL);
// tools_init_code begin:
	px_mutex_init(&mutex,NULL);
	px_condattr_init(&condattr);
	px_condattr_set(&condattr);
	px_cond_init(&cond,&condattr);
	for(i=0;i<get_ar_count(tida);i++){
		px_thread_create(&tida[i],NULL,p_routine_array[i],NULL);
		px_seminit(&sema[i],0,0);
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
		px_semdestroy(&sema[i]);
		px_thread_join(tida[i],NULL);
	}
	px_cond_destroy(&cond);
	px_condattr_destroy(&condattr);
	px_mutex_destroy(&mutex);	
	return 0;
}