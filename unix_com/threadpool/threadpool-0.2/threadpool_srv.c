#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <lzl/misc.h>
#include <lzl/px_thread.h>
#include <lzl/slog.h>
#include <signal.h>
#include "threadpool.c"
threadpool_t *p_threadpool=NULL;
#define def_test_func(x) \
void *tp_test_func_##x(void *args){\
	struct timespec ts = {0,1000000*100};\
	int num=0;\
	num=*(int*)args;\
	FREE(args);\
	do{\
		inf("%s,%ld,%d is start",__func__,pthread_self(),num);\
		usleep(1000000*0.5);\
		inf("%s,%ld,%d is done",__func__,pthread_self(),num);\
	}while(0);\
	return NULL;\
}
def_test_func(0)
def_test_func(1)
def_test_func(2)
def_test_func(3)
def_test_func(4)
def_test_func(5)
def_test_func(6)
def_test_func(7)
def_test_func(8)
def_test_func(9)
def_test_func(10)
def_test_func(11)
def_test_func(12)
def_test_func(13)
def_test_func(14)
def_test_func(15)
tp_task_func_t task_func_tbl[]={
	&tp_test_func_0,
	&tp_test_func_1,
	&tp_test_func_2,
	&tp_test_func_3,
	&tp_test_func_4,
	&tp_test_func_5,
	&tp_test_func_6,
	&tp_test_func_7,
	&tp_test_func_8,
	&tp_test_func_9,
	&tp_test_func_10,
	&tp_test_func_11,
	&tp_test_func_12,
	&tp_test_func_13,
	&tp_test_func_14,
	&tp_test_func_15,
};
int add_count=0;
void signal_handle(int signo){
	int ret=0;
	switch(signo){
	case 34:{
		inf("recive signal:%d!",signo);
		int *p_num=(int*)calloc(1,sizeof(int));
		if(!p_num)break;
		*p_num=add_count++;
		ret=threadpool_task_add(p_threadpool,task_func_tbl[add_count%15],p_num);
		if(ret<0)break;
		inf("threadpool_task_add done!");
		break;
	}
	case 35:{
		inf("recive signal:%d!",signo);
		ret=threadpool_destory(p_threadpool);
		if(ret<0)break;
		inf("threadpool_destory done!");
		break;
	}
	case 36:{
		int i=0;
		inf("recive signal:%d!",signo);
		add_count=0;
		for(i=0;i<10;i++){
			inf("in signal stop %d s",i );
			raise(37);
			sleep(1);
		}
		inf("threadpool_task_add clear,add_count=%d!",add_count);
		break;
	}
	case 37:{
		inf("recive signal:%d!",signo);
		px_cond_broadcast(&p_threadpool->tp_cond);
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
	for(i=SIGRTMIN;i<=SIGRTMAX;i++){
		signal(i,signal_handle);
	}
	p_threadpool=threadpool_create(8,15);
	sleep(2);
	do{
		for(i=0;i<20;i++){
			int *p_num=(int*)calloc(1,sizeof(int));
			if(!p_num)return -1;
			*p_num=add_count++;
			// if(i==14)inf("threadpool_task_add done!---------------------");
			ret=threadpool_task_add(p_threadpool,task_func_tbl[i%15],p_num);
			if(i==14)inf("threadpool_task_add done!---------------------");			
			if(ret<0)return -1;
		}
		sleep(1);
		// inf("threadpool_task_add done!---------------------");
	}while(1);
	while(1)pause();
	return 0;
}