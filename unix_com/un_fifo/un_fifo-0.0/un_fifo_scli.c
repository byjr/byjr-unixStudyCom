#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include "un_fifo.c"
#include <lzl/px_sem.h>
#include <lzl/px_shm.h>
usr_shm_t *pxshm=NULL;
sem_t *p_sem=NULL;
int cmd_handle_init(){
	int ret=0;
	px_shm_get((void **)&pxshm,CMD_SHM_NAME);
	ret=px_semopen(&p_sem,CMD_SEM_NAME,0);
	if(ret<0)exit(-1);
	return 0;
}
int argv_to_argl(char argl[],char *argv[],int len){
	int i=0,rt_len=0,rt_idx=0;
	bzero(argl,len);
	for(i=0;;i++){
		if(!argv[i]){			
			return 0;
		}
		rt_len=strlen(argv[i]);
		rt_idx+=rt_len;				
		if(rt_idx+2>=len){
			err("argl no enough buf!");
			return -1;
		}
		strcat(argl,argv[i]);
		rt_idx++;
		strcat(argl,CMD_SEPARATOR);
		inf("argl:%s",argl);		
	}
	return 0;
}
int main(int argc,char *argv[])
{
	int ret=0,i=0,rt_idx,rt_len=0;
	log_init(NULL);
	cmd_handle_init();
	do{
		argv_to_argl(pxshm->cmd_buf,argv,sizeof(pxshm->cmd_buf));
		inf(pxshm->cmd_buf);
		if(!strstr(__FILE__,"scli")){
			px_sempost(p_sem,1);
		}
	}while(0);
	return 0;
}



