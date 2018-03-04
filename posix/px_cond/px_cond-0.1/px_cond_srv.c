#include <signal.h>
#include "px_cond.c"
#include "lzl/px_mutex.h"
#include "lzl/px_shm.h"
#include "lzl/fifo_cmd.h"
#include "lzl/misc.h"
usr_shm_t *px_shm=NULL;
int start_handle(void *args){
	char ** argv=(char **)args;
	IS_ARG_COUNT_LESS_THAN(1);
	px_mutex_lock(&(px_shm->mtx));
	exec_cmd2("echo ---:%s > /tmp/ttt.tmp",argv[1]);
	px_cond_signal(&(px_shm->cond));
	px_mutex_unlock(&(px_shm->mtx));	
	return 0;
}

fifo_cmd_t fifo_cmd_tbl[]={
	ADD_CMD_ITEM(start)
};

int tools_init(void *args){
	int ret=px_shm_get(&px_shm,"/shm1x");
	if(ret<0) return -1;
	pthread_mutexattr_t attr;
	px_mutexattr_init(&attr);
	 ret=px_mutexattr_set(&attr);
	if(ret<0)return -1;
	ret=px_mutex_init(&(px_shm->mtx),&attr);
	if(ret<0)return -1;
	pthread_condattr_t condAttr;
	px_condattr_init(&condAttr);
	ret=px_condattr_set(&condAttr);
	if(ret<0)return 0;
	ret=px_cond_init(&(px_shm->cond),&condAttr);
	if(ret<0)return -1;
	return 0;
}
int main(int argc,char *argv[]){
	log_init("l=11111");	
	int ret=tools_init(NULL);
	if(ret<0) return -1;	
	pid_t pid=fork();
	switch(pid){
	case 0:{//子进程
			inf("my_pid is:%d",getpid());
			int ret=fifo_cmd_init();
			if(ret<0)return -1;
			do{
				fifo_cmd_wait();
				fifo_cmd_proc(fifo_cmd_tbl,getCount(fifo_cmd_tbl));				
			}while(1);
		}
		break;
	case -1:
			err("fork failure!");
		break;
	default:
		break;
	}
	inf("my_pid is:%d",getpid());
	do{
		px_mutex_lock(&(px_shm->mtx));
		px_cond_wait(&(px_shm->cond),&(px_shm->mtx));
		system("cat /tmp/ttt.tmp");
		px_mutex_unlock(&(px_shm->mtx));		
	}while(1);
}