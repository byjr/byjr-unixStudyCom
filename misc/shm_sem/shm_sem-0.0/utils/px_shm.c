#include "px_shm.h"

usr_shm_t *shm=NULL;
void px_shm_get(void)
{
	int ret=0,fd=0,fail=1;
	fd=shm_open(SHM_PATH,O_RDWR|O_CREAT,0666);
	if(fd <= 0){
		show_error(fd,"shm_open");
		goto Exit0;
	}
	ret=ftruncate(fd,sizeof(usr_shm_t));
	if(ret < 0){
		show_error(ret,"ftruncate");
		goto Exit1;
	}
	shm=mmap(NULL,sizeof(usr_shm_t),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(NULL == shm){
		show_error(shm,"mmap");
		goto Exit1;
	}
	fail=0;
Exit1:	
	close(fd);
Exit0:	
	if(fail)exit(-1);
}
void shm_mem_init(void){
	int ret=0;
	
	ret=px_seminit(&shm->a2i_work_sem,1,0);
	if(ret<0)exit(-1);
	
	ret=px_seminit(&shm->a2i_stop_sem,1,0);
	if(ret<0)exit(-1);
}


