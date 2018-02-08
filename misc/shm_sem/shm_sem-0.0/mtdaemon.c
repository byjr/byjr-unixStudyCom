#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<signal.h>
#include<lzl/slog.h>
#include<lzl/px_sem.h>
#include "px_shm.h"
int main(int argc,char *argv[]){
	int ret=0,i=0;
	log_init(NULL);
	px_shm_get();
	shm_mem_init();
	do{
		inf("");
		shm->a2i_cmd=0;
		px_sempost(&shm->a2i_stop_sem,1);
		px_sempost(&shm->a2i_work_sem,1);
	}while(0);
	while(1)pause();
}