#include<slog/slog.h>
#include<pthread.h>
#include <unistd.h>
#include "my_sem.h"
#define NUM_THREAD 100
pthread_t thread[NUM_THREAD]={0};
int flag[NUM_THREAD]={0};
void* thread_proc(void *arg){
	int n=*(int*)arg;
	while(1){
		ipt("thread_proc: %d",n);
		usleep(1000*1000);
	}
}
int main(int argc,char **argv){
	int ret=0;
	if(log_init(NULL)<0){
		war("log_init fail!");
	}
	int i=0;
	for(;i<NUM_THREAD;i++){
		flag[i]=i;
		if((ret=pthread_create(&thread[i],NULL,thread_proc,&flag[i]))){
			err("pthread_creat fail,ret=%d",ret);
			return -1;
		}
		inf("pthread_create %d",i);
	}
	while(1){
		inf("main");
		usleep(100*1000);
	}
	return 0;
}