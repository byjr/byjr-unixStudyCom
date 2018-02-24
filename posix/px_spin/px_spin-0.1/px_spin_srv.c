#include <signal.h>
#include "px_spin.h"
#include "lzl/px_shm.h"
#include "lzl/fifo_cmd.h"
usr_shm_t *px_shm=NULL;
size_t loop_count=0;
int start_handle(void *args){
	char ** argv=(char **)args;
	IS_ARG_COUNT_LESS_THAN(1);
	loop_count=argv[1][0]-'0';
	px_spin_unlock(&(px_shm->spLock));	
	return 0;
}

fifo_cmd_t fifo_cmd_tbl[]={
	ADD_CMD_ITEM(start)
};

int tools_init(void *args){
	int ret=px_shm_get(&px_shm,"/shm1x");
	if(ret<0) return -1;
	ret=px_spin_init(&(px_shm->spLock),PTHREAD_PROCESS_SHARED);
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
				fifo_cmd_proc(fifo_cmd_tbl,get_ar_count(fifo_cmd_tbl));				
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
		// int ret=px_spin_lock(&(px_shm->spLock));
		int ret=px_spin_trylock(&(px_shm->spLock));		
		if(ret<0) continue;
		war("loop_count=%u",++loop_count);
		// px_mutex_unlock(&(px_shm->mtx));		
	}while(1);
}