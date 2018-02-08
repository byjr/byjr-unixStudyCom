#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include "px_barrier.h"
#include <lzl/misc.h>
#include <lzl/slog.h>
int px_barrierattr_set(pthread_barrierattr_t *p_attr)
{
	int ret=0;
	px_barrierattr_setpshared(p_attr,PTHREAD_PROCESS_SHARED);
	return 0;	
}
int px_barrierattr_show(pthread_barrierattr_t *p_attr)
{
	int ret=0;
	int pshared=0;
	ret=pthread_barrierattr_getpshared(p_attr,&pshared);
	if(pshared==PTHREAD_PROCESS_SHARED){
		inf("系统范围");
	}else if(pshared==PTHREAD_PROCESS_PRIVATE){
		inf("进程范围");
	}
	return 0;
}


