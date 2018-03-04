#include <signal.h>
#include <stdlib.h>
#include "px_rwlock.c"
#include "lzl/px_shm.h"
#include "lzl/fifo_cmd.h"
#include "lzl/misc.h"

usr_shm_t *px_shm=NULL;
int rlock_handle(void *args){
	struct timespec ts = {0};
	char ** argv=(char **)args;
	IS_ARG_COUNT_LESS_THAN(1);
	pid_t pid=fork();
	if(pid<0)return -1;
	if(pid>0)return 0;
	ts.tv_sec=atol(argv[1]);	
	do{
		int ret=px_rwlock_rdlock(&px_shm->rwLock);
		if(ret<0)return -1;
		war("%s:%d is succeed",__func__,getpid());
		exit(0);
	}while(0);
	return 0;
}
int wlock_handle(void *args){
	pid_t pid=fork();
	if(pid<0)return -1;
	if(pid>0)return 0;
	do{
		int ret=px_rwlock_wrlock(&px_shm->rwLock);
		if(ret<0)return -1;
		war("%s:%d is succeed",__func__,getpid());
		exit(0);		
	}while(0);
	return 0;
}
int unlock_handle(void *args){
	pid_t pid=fork();
	if(pid<0)return -1;
	if(pid>0)return 0;
	do{
		int ret=px_rwlock_unlock(&px_shm->rwLock);
		if(ret<0)return -1;
		war("%s:%d is succeed",__func__,getpid());
		exit(0);
	}while(0);
	return 0;
}
int frlock_handle(void *args){
	
	do{
		int ret=px_rwlock_rdlock(&px_shm->rwLock);
		if(ret<0)return -1;
		war("%s:%d is succeed",__func__,getpid());
	}while(0);
	return 0;
}
int fwlock_handle(void *args){
	
	do{
		int ret=px_rwlock_wrlock(&px_shm->rwLock);
		if(ret<0)return -1;
		war("%s:%d is succeed",__func__,getpid());
	}while(0);
	return 0;
}
fifo_cmd_t fifo_cmd_tbl[]={
	ADD_CMD_ITEM(rlock)
	ADD_CMD_ITEM(wlock)
	ADD_CMD_ITEM(unlock)
	ADD_CMD_ITEM(fwlock)
	ADD_CMD_ITEM(frlock)
};

int tools_init(void *args){
	signal(SIGCHLD,SIG_IGN);
	int ret=px_shm_get(&px_shm,"/shm1x");
	if(ret<0) return -1;
	pthread_rwlockattr_t rwlAttr={0};
	px_rwlockattr_init(&rwlAttr);
	// px_rwlockattr_set(&rwlAttr);
	// pthread_rwlockattr_setkind_np(&rwlAttr,PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
	px_rwlockattr_show(&rwlAttr);
	px_rwlock_init(&px_shm->rwLock,&rwlAttr);
	return 0;
}
int main(int argc,char *argv[]){
	log_init("l=11111");	
	int ret=tools_init(NULL);
	if(ret<0) return -1;
	pid_t pid=fork();
	if(pid<0)return -1;
	if(pid>0){
		ret=fifo_cmd_init("/tmp/subc.fifo");
		if(ret<0)return -1;
		do{
			fifo_cmd_wait();
			fifo_cmd_proc(fifo_cmd_tbl,getCount(fifo_cmd_tbl));				
		}while(1);		
	};	
	ret=fifo_cmd_init("/tmp/cmd.fifo");
	if(ret<0)return -1;
	do{
		fifo_cmd_wait();
		fifo_cmd_proc(fifo_cmd_tbl,getCount(fifo_cmd_tbl));				
	}while(1);
}