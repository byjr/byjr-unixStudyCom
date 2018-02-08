#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "px_mtxcond.c"
#include <lzl/cs_cmd.h>
#include <lzl/px_thread.h>
#include <lzl/px_sem.h>
#include <lzl/px_mutex.h>
#include <lzl/slog.h>
#if 1
typedef enum{
	IDX_MIN=-1,
	IDX_WAIT	,
	IDX_WAITD	,
	IDX_SIGNAL	,
	IDX_BDCT	,
	IDX_MAX,
}rw_idx_t;
px_mtxcondattr_t mtxcondattr={0};
px_mtxcond_t mtxcond={0};

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
		war("%s:%d/%ld is start",__func__,getpid(),pthread_self());		
		px_semwait(&sema[IDX_WAIT]);
		px_mtxcond_wait(&mtxcond);
		dbg("IDX_WAIT done!");
		// nanosleep(&ts, NULL);
	}while(1);
}
void *tdwait_routine(void *args){
	struct timespec tv;
	struct timespec ts = {1,0};
	struct timespec nts = {1,0};
	do{
		war("%s:%d/%ld is start",__func__,getpid(),pthread_self());		
		px_semwait(&sema[IDX_WAITD]);
		clock_gettime(CLOCK_MONOTONIC,&tv);
		tv.tv_sec+=20;	
		px_mtxcond_tdwait(&mtxcond,&tv);
		dbg("IDX_WAITD done!");
		// nanosleep(&nts, NULL);		
	}while(1);
}
void *signal_routine(void *args){
	struct timespec ts = {1,0};
	do{
		war("%s:%d/%ld is start",__func__,getpid(),pthread_self());		
		px_semwait(&sema[IDX_SIGNAL]);
		war("IDX_SIGNAL start!");
		px_mtxcond_signal(&mtxcond);
		war("IDX_SIGNAL done!");
	}while(1);
}
void *broadcast_routine(void *args){
	struct timespec ts = {1,0};
	do{
		war("%s:%d/%ld is start",__func__,getpid(),pthread_self());		
		px_semwait(&sema[IDX_BDCT]);
		war("IDX_BDCT start!");
		px_mtxcond_broadcast(&mtxcond);
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
	ret=px_mtxcondattr_show(&mtxcondattr);
	if(ret)return -1;
	return 0;
}
int aset_handle(void *args){
	int ret=0;
	ret=px_mtxcondattr_set(&mtxcondattr);
	// ret=px_mtxcondattr_show(&mtxcondattr);
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
#endif
int main(int argc,char **argv){
#if 1	
	int ret=0,i=0;
	log_init(NULL);
// tools_init_code begin:
	px_mtxcond_init(&mtxcond,NULL);
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
	px_mtxcond_destroy(&mtxcond);
	px_mtxcondattr_destroy(&mtxcondattr);
#endif	
	return 0;
}