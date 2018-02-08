#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <lzl/misc.h>
#include <lzl/px_thread.h>
#include <lzl/slog.h>
#include <signal.h>
#include "threadpool.c"
threadpool_t threadpool={0};
void * tp_test_func(void *args){
	struct timespec ts = {0,1000000*100};			
	int num=0;
	num=*(int*)args;
	FREE(args);
	do{		
		// nanosleep(&ts, NULL);
		war("%s:%d/%ld num:%d is done",__func__,getpid(),pthread_self(),num);
	}while(0);
	return NULL;
}
static int add_count=0; 
void signal_handle(int signo){
	int ret=0;
	switch(signo){	
	case 34:{		
		inf("recive signal:%d!",signo);	
		int *p_num=(int*)calloc(1,sizeof(int));
		if(!p_num) break;
		*p_num=add_count++;;
		ret=threadpool_task_add(&threadpool,&tp_test_func,p_num);
		if(ret<0) {FREE(p_num);break;}
		inf("threadpool_task_add done,add_count=%d!",add_count);
		break;		
	}
	case 35:{
		inf("recive signal:%d!",signo);	
		ret=threadpool_destory(&threadpool);
		if(ret<0)break;
		inf("threadpool_destory done!");		
		break;
	}
	case 36:{
		inf("recive signal:%d!",signo);	
		add_count=0;
		inf("threadpool_task_add clear,add_count=%d!",add_count);
		break;
	}
	case 37:{
		inf("recive signal:%d!",signo);	
		px_mutex_lock(&threadpool.tp_mtx);
		px_cond_broadcast(&threadpool.tp_cond);
		px_mutex_unlock(&threadpool.tp_mtx);
		inf("threadpool_task_add clear,add_count=%d!",add_count);
		break;
	}	
	default:
		inf("recive signal:%d!",signo);	
		break;
	}
}
int main(int argc,char **argv){
	int ret=0,i=0;	
	log_init(NULL);
	for(i=SIGRTMIN;i<=SIGRTMAX;i++)
		signal(i,signal_handle);
	ret=threadpool_create(&threadpool,8,16);
	if(ret<0)return -1;	
	sleep(1);
	do{		
		for(i=0;i<20;i++){
			int *p_num=(int*)calloc(1,sizeof(int));
			if(!p_num)return -1;
			*p_num=add_count++;
			ret=threadpool_task_add(&threadpool,&tp_test_func,p_num);
			if(ret<0)return -1;
			inf("threadpool_task_add done!");
		}
	}while(0);
	while(1);
	return 0;
}