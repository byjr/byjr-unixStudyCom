#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include "px_sem.h"

int px_seminit(sem_t *p_sem,int pshared,unsigned int value)
{
	int ret=0;
	ret=sem_init(p_sem,pshared,value);
	if(-1==ret){
		perror("sem_init");
		return -1;
	}
	return 0;
}
int px_semopen(sem_t **pp_sem,char *name,unsigned int value)
{
	sem_t *p_sem=NULL;	
	p_sem=sem_open(name,O_CREAT,0644,value);
	if(SEM_FAILED==p_sem){
		perror("sem_open");
		return -1;
	}
	*pp_sem=p_sem;
	return 0;
}
int px_semclose(sem_t *p_sem)
{
	if(sem_close(p_sem)<0){
		perror("sem_close");
		return -1;
	}
	return 0;
}
int px_semgetvalue(unsigned int *p_val,sem_t *p_sem)
{
	int ret=0;
	ret=sem_getvalue(p_sem,p_val);
	if(-1==ret){
		perror("sem_getvalue");
		return -1;
	}
	 *p_val=ret;
	return 0;
}
int px_sempost(sem_t *p_sem,unsigned int max)
{
	int ret=0,value=0;
	if(px_semgetvalue(&value,p_sem)<0){
		return -1;
	}
	if(value < max){
		ret=sem_post(p_sem);
		if(-1==ret){
			perror("sem_post");
			return -1;
		}
	}
	return 0;
}
int px_semwait(sem_t *p_sem){
	int ret=0;
	while(1){
		ret=sem_wait(p_sem);
		if(-1==ret){
			if(errno=EINTR)continue;
			perror("sem_wait");
			return -1;
		}
		return 0;
	}
}
int px_semtrywait(sem_t *p_sem)
{
	int ret=0;
	ret=sem_trywait(p_sem);
	if(-1==ret){
		// perror("sem_trywait");
		return -1;
	}
	return 0;
}
int px_semtimedwait(sem_t *p_sem,int sec)
{
	int ret=0;
	struct timespec ts={0};
	ret=clock_gettime(CLOCK_REALTIME, &ts);
	if(-1==ret){
		perror("clock_gettime");
	}
	ts.tv_sec+=sec;
	ret=sem_timedwait(p_sem,&ts);
	if(-1==ret){
		perror("sem_timedwait");
		return -1;
	}
	return 0;
}
int px_semdestroy(sem_t *p_sem)
{
	int ret=0;
	ret=sem_destroy(p_sem);
	if(-1==ret){
		perror("sem_destroy");
		return -1;
	}
	return 0;
}
int px_semunlink(const char* path)
{
	int ret=0;
	ret=sem_unlink(path);
	if(-1==ret){
		perror("sem_unlink");
		return -1;
	}
	return 0;
}