#include <stdio.h>
#include <string.h>
#include <lzl/sv_sem.h>
#include <lzl/slog.h>
#include "sv_shm.c"
int shmid=0;
shm_st *p_shm=NULL;
int lock_shm_sem=0;
char write_buf[SHM_TEXT_SIZE]="";
int main(int argc,char **argv)  
{
	sv_shmget(&shmid,sizeof(shm_st),TTT_SHM_SIPC);
	sv_shmat((void **)&p_shm,shmid);
	sv_semget(&lock_shm_sem,1,LOCK_SEM_SIPC);
	sv_semset(lock_shm_sem,0,0);
	log_init(NULL);
	while(1){
		war("please input some inf:")
		memset(write_buf,0,sizeof(write_buf));
		fgets(write_buf,SHM_TEXT_SIZE-1,stdin);
		
		memset(p_shm->txt,0,sizeof(p_shm->txt));
		strncpy(p_shm->txt,write_buf,sizeof(p_shm->txt)-1);		
		sv_semset(lock_shm_sem,0,+1);		
	}
	return 0;
} 
