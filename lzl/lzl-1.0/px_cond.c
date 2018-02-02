#include "px_cond.h"
int px_thread_condattr_set(pthread_condattr_t *p_attr)
{
	px_thread_condattr_setpshared(p_attr,PTHREAD_PROCESS_SHARED);
	__clockid_t cid=CLOCK_MONOTONIC;//条件变量现在只支持：墙上时钟和单调时钟
	px_thread_condattr_setclock(p_attr,cid);
}
int px_thread_condattr_show(pthread_condattr_t *p_attr)
{
	int shared=0;
	px_thread_condattr_getpshared(p_attr,&shared);
	inf("条件作用域为:%s",	shared==PTHREAD_PROCESS_SHARED	?"系统范围":\
							shared==PTHREAD_PROCESS_PRIVATE	?"进程范围":\
							"???");
	__clockid_t cid=0;
	px_thread_condattr_getclock(p_attr,&cid);
	inf("时钟类型为  :%s",cid==CLOCK_REALTIME			?"墙上时钟":\
						cid==CLOCK_MONOTONIC			?"单调时钟":\
						cid==CLOCK_MONOTONIC_RAW		?"开机时钟":\
						cid==CLOCK_PROCESS_CPUTIME_ID	?"进程时钟":\
						cid==CLOCK_THREAD_CPUTIME_ID	?"线程时钟":\
						"???");
														
	return 0;
}


