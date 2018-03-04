#include <signal.h>
#include <stdlib.h>
#include "px_barrier.c"
#include "lzl/px_shm.h"
#include "lzl/fifo_cmd.h"
#include "lzl/misc.h"

usr_shm_t *px_shm=NULL;
int sub_process(void *args){
	struct timespec ts = {1,0};	
	char ** argv=(char **)args;
	inf("%s:%d is start!",__func__,getpid());
	px_barrier_wait(&px_shm->barrier);
	war("%s:%d is done !",__func__,getpid());
	nanosleep(&ts, NULL);	
	return 0;	
}
int start_handle(void *args){
	char ** argv=(char **)args;
	IS_ARG_COUNT_LESS_THAN(1);
	int i=0;
	for(i=0;i<atoi(argv[1]);i++){
		pid_t pid=fork();
		switch(pid){
		case 0:
			sub_process(NULL);
			break;
		case -1:
			err("fork failure!");
			break;
		default:
			break;
		}
	}
	return 0;
}
fifo_cmd_t fifo_cmd_tbl[]={
	ADD_CMD_ITEM(start)
};

int tools_init(void *args){
	int ret=px_shm_get(&px_shm,"/shm1x");
	if(ret<0) return -1;
	pthread_barrierattr_t barrierattr={0};
	px_barrierattr_init(&barrierattr);
	px_barrierattr_setpshared(&barrierattr,PTHREAD_PROCESS_SHARED);
	px_barrier_init(&px_shm->barrier,&barrierattr,5);
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
		// px_mutex_lock(&(px_shm->mtx));
		// px_cond_wait(&(px_shm->cond),&(px_shm->mtx));
		// system("cat /tmp/ttt.tmp");
		// px_mutex_unlock(&(px_shm->mtx));
		pause();
	}while(1);
}