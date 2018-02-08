#include "px_thread.c"
#include <unistd.h>
#include <signal.h>
#include <lzl/cs_cmd.h>
#include <lzl/px_sem.h>
sem_t px_sem={0};
pthread_attr_t attr={0};
pthread_t px_thread=0;
pthread_once_t once_ctl=PTHREAD_ONCE_INIT;
pthread_once_t once_ctl_sub=PTHREAD_ONCE_INIT;

void *px_start_routine(void *args);
int set_handle(void *args){	
	char **argv=(char **)args;
	px_thread_set_attr(&attr);	
	return 0;
}
int get_handle(void *args){	
	char **argv=(char **)args;
	px_thread_show_attr(&attr);
	return 0;
}
void *sub_start_routine(void *args){
	do{
		inf("sub_thread %08ld is running...",pthread_self());
		usleep(1*1000*1000);
	}while(1);
}
void *once_routine(){
	px_thread_create(&px_thread,NULL,&px_start_routine,NULL);
	return NULL;
}
void *once_routine_sub(){
	px_thread_create(&px_thread,NULL,&sub_start_routine,NULL);
	return NULL;
}
void *px_start_routine(void *args){
	// px_thread_set_cancel_state(PTHREAD_CANCEL_DISABLE);
	// px_thread_set_cancel_type(PTHREAD_CANCEL_DEFERRED);
	// pthread_once(&once_ctl,&once_routine);
	// pthread_once(&once_ctl_sub,&once_routine_sub);
	do{
		inf("px_thread %08ld is running...",pthread_self());
		if(!px_semtrywait(&px_sem)){
			dbg("px_thread yield remain times pices!");
			px_thread_yield();
		}
		inf("111");
		pthread_testcancel();
		inf("222");
		usleep(1*1000*1000);
		inf("333");
		pthread_testcancel();
		inf("444");
		usleep(1*1000*1000);			
	}while(1);
}
int create_handle(void *args){	
	char **argv=(char **)args;
	int ret=0;
	ret=pthread_create(&px_thread,NULL,&px_start_routine,args);
	if(ret){
		show_errno(ret,__func__);
		exit(-1);
	}
	inf("px_thread %ld create succeed!",px_thread);	
	return 0;
}
int cancel_handle(void *args){	
	char **argv=(char **)args;	
	int ret=0;
	IS_ARG_COUNT_LESS_THAN(2);	
	pthread_t px_tid=atol(argv[2]);
	war("will to cancel %ld",px_tid);
	px_thread_cancel(px_tid);
	war("%ld cancel complate!",px_tid);	
	return 0;
}
int get_an_handle(void *args){	
	char **argv=(char **)args;	
	int ret=0;
	IS_ARG_COUNT_LESS_THAN(2);
	pthread_t px_tid=atol(argv[2]);
	ret=pthread_getattr_np(px_tid,&attr);
	if(ret){
		show_errno(ret,__func__);
		return -1;	
	}
	px_thread_show_attr(&attr);
	return 0;
}
int get_adn_handle(void *args){	
	char **argv=(char **)args;	
	int ret=0;
	ret=pthread_getattr_default_np(&attr);
	if(ret){
		show_errno(ret,__func__);
		return -1;	
	}
	px_thread_show_attr(&attr);
	return 0;
}
int detach_handle(void *args){	
	char **argv=(char **)args;	
	int ret=0;
	IS_ARG_COUNT_LESS_THAN(2);		
	pthread_t px_tid=atol(argv[2]);	
	ret=pthread_detach(px_tid);
	if(ret){
		show_errno(ret,__func__);
		return -1;	
	}
	inf("%ld detach complate!",px_tid);
	return 0;
}
int yield_handle(void *args){	
	px_sempost(&px_sem,1);
	return 0;
}
struct sched_param pro_para={5};
int rtset_handle(void *args){	
	px_thread_setschedparam(px_thread,SCHED_RR,&pro_para);
	return 0;
}
cs_cmd_t cs_cmd_tbl[]={
	ADD_CMD_ITEM(get)
	ADD_CMD_ITEM(set)
	ADD_CMD_ITEM(create)
	ADD_CMD_ITEM(cancel)
	ADD_CMD_ITEM(get_an)
	ADD_CMD_ITEM(get_adn)
	ADD_CMD_ITEM(detach)
	ADD_CMD_ITEM(yield)
	ADD_CMD_ITEM(rtset)	
};
int tls_init(){
	int ret=0,fail=1;	
	ret = px_thread_attr_init(&attr);
	if (ret)goto Exit0;
	px_seminit(&px_sem,0,0);
	px_thread_set_attr(&attr);
	px_thread_create(&px_thread,&attr,&px_start_routine,NULL);
Exit0:	
	if(fail)return -1;
	return 0;
}
int tls_deinit(){
	int ret=0,fail=1;	
	ret = pthread_attr_destroy(&attr);
	if (ret){		
		show_error(ret, "pthread_attr_destroy");
		goto Exit0;
	}
Exit0:	
	if(fail)return -1;
	return 0;
}
int main(int argc,char **argv){
	int ret=0;
	log_init(NULL);
	tls_init();
	cs_cmd_init(SIGRTMIN);
	int count=sizeof(cs_cmd_tbl)/sizeof(cs_cmd_tbl[0]);
	do{
		cs_cmd_wait();
		war("px_thread %08ld is running...",pthread_self());
		cs_cmd_proc(cs_cmd_tbl,count,px_shm->cmd_buf);
	}while(1);
	tls_deinit();
	return 0;
}



