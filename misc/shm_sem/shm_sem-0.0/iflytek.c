#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<signal.h>
#include<lzl/px_thread.h>
#include<lzl/px_sem.h>
#include<lzl/slog.h>
#include "px_shm.h"
sem_t ifly_sem={0};
pthread_t tid=0;
void *doss_api_proc(void * args){
	int ret=0,i=0;
	while(1){
		px_semtrywait(&shm->a2i_stop_sem);
		ret=px_semwait(&ifly_sem);
		if(ret<0)continue;
		inf("recice cmd:%d",shm->a2i_cmd);
		for(i=0;i<10;i++){
			usleep(1000*1000);
			ret=px_semtrywait(&shm->a2i_stop_sem);
			if(!ret){
				war("recice stop!");
				break;
			}
		}		
	}	
}
int main(){
	int ret=0,i=0;
	log_init(NULL);
	px_shm_get();
	shm_mem_init();	
	px_seminit(&ifly_sem,0,0);	
	px_thread_create(&tid,NULL,doss_api_proc,NULL);	
	while(1){
		inf("");		
		ret=px_semwait(&shm->a2i_work_sem);
		if(ret<0)continue;
		inf("");
		px_sempost(&ifly_sem,1);
		px_semwait(&shm->a2i_stop_sem);			
	}
}