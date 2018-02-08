#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include "px_mutex.h"
#include <lzl/misc.h>
#include <lzl/slog.h>
int px_mutexattr_set(pthread_mutexattr_t *p_attr)
{
	px_thread_mutexattr_setprioceiling(p_attr,2);
	px_thread_mutexattr_setprotocol(p_attr,PTHREAD_PRIO_INHERIT);
	px_thread_mutexattr_setpshared(p_attr,PTHREAD_PROCESS_SHARED);
	px_thread_mutexattr_setrobust(p_attr,1);
	px_thread_mutexattr_settype(p_attr,PTHREAD_MUTEX_RECURSIVE);
}
int px_mutexattr_show(pthread_mutexattr_t *p_attr)
{
	int prioceiling=0;
	px_thread_mutexattr_getprioceiling(p_attr,&prioceiling);
	inf("优先级上限为:%d",prioceiling);
	int protocol=0;
	px_thread_mutexattr_getprotocol(p_attr,&protocol);
	inf("协议属性为:%s",protocol==PTHREAD_PRIO_NONE		?"不影响线程调度":\
						protocol==PTHREAD_PRIO_INHERIT	?"优先级继承":\
						protocol==PTHREAD_PRIO_INHERIT	?"优先级保护":\
						"???");
	int shared=0;
	px_thread_mutexattr_getpshared(p_attr,&shared);
	inf("互斥锁作用域为:%s",shared==PTHREAD_PROCESS_SHARED	?"系统范围":\
							shared==PTHREAD_PROCESS_PRIVATE	?"进程范围":\
							"???");
	int robust=0;
	px_thread_mutexattr_getpshared(p_attr,&robust);
	inf("鲁棒值为:%d",robust);
	int type=0;
	px_thread_mutexattr_gettype(p_attr,&type);
	inf("互斥锁类型为:%s",	type==PTHREAD_MUTEX_NORMAL		?"普通锁":\
							type==PTHREAD_MUTEX_ERRORCHECK	?"检错锁":\
							type==PTHREAD_MUTEX_RECURSIVE	?"递归锁":\
							type==PTHREAD_MUTEX_DEFAULT		?"默认锁":\
															"???");
	return 0;
}


