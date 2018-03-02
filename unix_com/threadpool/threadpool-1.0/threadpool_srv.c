#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>
#include <lzl/misc.h>
#include <lzl/px_thread.h>
#include <lzl/slog.h>
#include <lzl/fifo_cmd.h>
#include "threadpool.c"
size_t add_count=0;
pthread_t pxtid;	
threadpool_t *pTP=NULL;
#define def_test_func(x) \
void *tp_test_func_##x(void *args){\
	struct timespec ts = {0,1000000*100};\
	int num=0;\
	num=*(int*)args;\
	FREE(args);\
	do{\
		inf("%s,%ld,%d is start",__func__,pthread_self(),num);\
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
int dsty_handle(void *args){
	char ** argv=(char **)args;
	int ret=threadpool_destory(pTP);
	if(ret<0)return -1;
	return 0;
}
int addt_handle(void *args){
	char ** argv=(char **)args;
	int *p_num=(int*)calloc(1,sizeof(int));
	if(!p_num)return -1;
	IS_ARG_COUNT_LESS_THAN(2);
	*p_num=argv[2][0]-'0';
	int ret=threadpool_task_add(pTP,task_func_tbl[argv[1][0]-'0'],p_num);
	if(ret<0)return -1;
	return 0;
}
char add_ctrl_flag=0;
int addc_handle(void *args){
	char ** argv=(char **)args;
	if(argv[1][0]=='0'){
		add_ctrl_flag=0;
	}else{
		add_ctrl_flag=1;
	}
	return 0;
}
fifo_cmd_t fifo_cmd_tbl[]={
	ADD_CMD_ITEM(dsty)
	ADD_CMD_ITEM(addt)
	ADD_CMD_ITEM(addc)
};
void *start_routinue(void *args){
	int ret=fifo_cmd_init();
	if(ret<0)return NULL;
	do{
		fifo_cmd_wait();
		fifo_cmd_proc(fifo_cmd_tbl,getArrayCount(fifo_cmd_tbl));				
	}while(1);	
}
int main(int argc,char *argv[]){
	log_init("l=11111");
	int ret=px_thread_create(&pxtid,NULL,start_routinue,NULL);
	if(ret<0)return -1;
	pTP=threadpool_create(8,15);
	do{
		int i=0;
		for(i=0;i<20;i++){
			if(add_ctrl_flag){
				int *p_num=(int*)calloc(1,sizeof(int));
				if(!p_num)return -1;
				*p_num=add_count++;
				// if(i==14)inf("threadpool_task_add done!---------------------");
				ret=threadpool_task_add(pTP,task_func_tbl[i%15],p_num);
				if(i==14)inf("threadpool_task_add done!---------------------");			
				if(ret<0)return -1;				
			}
		}
		sleep(1);
		// inf("threadpool_task_add done!---------------------");
	}while(1);
}