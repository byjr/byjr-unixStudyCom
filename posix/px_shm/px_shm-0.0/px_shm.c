#include "px_shm.h"

int px_shm_get(void **p_ptr,const char *name)
{
	int ret=0,fd=0,fail=1;	
	fd=shm_open(name,O_RDWR|O_CREAT,0666);
	if(fd <= 0){
		show_error(fd,__func__);
		goto Exit0;
	}
	ret=ftruncate(fd,PX_SHM_INIT_SIZE);
	if(ret < 0){
		show_error(ret,__func__);
		goto Exit0;
	}
	*p_ptr=mmap(NULL,PX_SHM_INIT_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(NULL == *p_ptr){
		show_error(*p_ptr,__func__);
		goto Exit0;
	}
	fail=0;
Exit0:
	close(fd);
	if(fail)exit(-1);
	return 0;
}


