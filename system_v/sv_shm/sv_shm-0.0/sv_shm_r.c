#include <stdio.h>
#include <string.h>
#include <lzl/sv_sem.h>
#include <lzl/slog.h>
#include "sv_shm.c"
int shmid=0;
shm_st *p_shm=NULL;
int lock_shm_sem=0;
char read_buf[SHM_TEXT_SIZE]="";
int main(int argc,char **argv)  
{
	sv_shmget(&shmid,sizeof(shm_st),TTT_SHM_SIPC);
	sv_shmat((void **)&p_shm,shmid);
	sv_semget(&lock_shm_sem,1,LOCK_SEM_SIPC);
	while(1){
		memset(read_buf,0,sizeof(read_buf));
		sv_semop(lock_shm_sem,0,-1);
		strncpy(read_buf,p_shm->txt,sizeof(read_buf)-1);		
		inf("read:%s",read_buf);
	}
	return 0;
} 