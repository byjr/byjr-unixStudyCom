#ifndef _PX_THREAD_H
#define _PX_THREAD_H 1
#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sched.h>
#include "slog.h"
#include "misc.h"

#if 0
//_______________________________________________________________________________________________________________
extern int pthread_attr_init(pthread_attr_t *__attr);
extern int pthread_attr_destroy(pthread_attr_t *__attr);
extern int pthread_attr_getaffinity_np(const pthread_attr_t *__attr,size_t __cpusetsize,cpu_set_t *__cpuset);
extern int pthread_attr_getdetachstate(const pthread_attr_t *__attr,int *__detachstate);
extern int pthread_attr_getguardsize(const pthread_attr_t *__attr,size_t *__guardsize);
extern int pthread_attr_getinheritsched(const pthread_attr_t *__attr,int *__inherit);
extern int pthread_attr_getschedparam(const pthread_attr_t *__attr,struct sched_param *__param);
extern int pthread_attr_getschedpolicy(const pthread_attr_t *__attr,int *__policy);
extern int pthread_attr_getscope(const pthread_attr_t *__attr,int *__scope);
extern int pthread_attr_getstack(const pthread_attr_t *__attr,void **__stackaddr,size_t *__stacksize);
// extern int pthread_attr_getstackaddr(const pthread_attr_t *__attr,void **__stackaddr);
extern int pthread_attr_getstacksize(const pthread_attr_t *__attr,size_t *__stacksize);
extern int pthread_attr_setaffinity_np(pthread_attr_t *__attr,size_t __cpusetsize,const cpu_set_t *__cpuset);
extern int pthread_attr_setdetachstate(pthread_attr_t *__attr,int __detachstate);
extern int pthread_attr_setguardsize(pthread_attr_t *__attr,size_t __guardsize);
extern int pthread_attr_setinheritsched(pthread_attr_t *__attr,int __inherit);
extern int pthread_attr_setschedparam(pthread_attr_t *__attr,const struct sched_param *__param);
extern int pthread_attr_setschedpolicy(pthread_attr_t *__attr,int __policy);
extern int pthread_attr_setscope(pthread_attr_t *__attr,int __scope);
extern int pthread_attr_setstack(pthread_attr_t *__attr,void *__stackaddr,size_t __stacksize);
// extern int pthread_attr_setstackaddr(pthread_attr_t *__attr,void *__stackaddr);
// extern int pthread_attr_setstacksize(pthread_attr_t *__attr,size_t __stacksize);
extern int pthread_setattr_default_np(const pthread_attr_t *__attr);
extern int pthread_getattr_default_np(pthread_attr_t *__attr);
extern int pthread_getattr_np(pthread_t __th,pthread_attr_t *__attr);
//线程行为控制
extern int pthread_setschedparam(pthread_t __target_thread,int __policy,const struct sched_param *__param);//调度策略+优先级
extern int pthread_getschedparam(pthread_t __target_thread,int *__policy,struct sched_param *__param);
extern int pthread_setaffinity_np(pthread_t __th,size_t __cpusetsize,const cpu_set_t *__cpuset);//CPU亲缘性
extern int pthread_setschedprio(pthread_t __target_thread,int __prio);//优先级
extern int pthread_getname_np(pthread_t __target_thread,char *__buf,size_t __buflen);//线程名
extern int pthread_setname_np(pthread_t __target_thread,const char *__name);
extern int pthread_getconcurrency(void);//并发度
extern int pthread_setconcurrency(int __level);
extern int pthread_detach(pthread_t __th);//分离运行
extern int pthread_create(pthread_t *__newthread,const pthread_attr_t *__attr,void *(*__start_routine)(void *),void *__arg);
extern int pthread_cancel(pthread_t __th);
extern void pthread_testcancel(void);
extern int pthread_setcancelstate(int __state,int *__oldstate);
extern int pthread_setcanceltype(int __type,int *__oldtype);
extern int pthread_yield(void);//放弃时间片剩余量
extern int pthread_once(pthread_once_t *__once_control,void(*__init_routine)(void));
extern void pthread_exit(void *__retval);
extern int pthread_join(pthread_t __th,void **__thread_return);
extern int pthread_timedjoin_np(pthread_t __th,void **__thread_return,const struct timespec *__abstime);
extern int pthread_tryjoin_np(pthread_t __th,void **__thread_return);
extern int pthread_atfork(void(*__prepare)(void),void(*__parent)(void),void(*__child)(void));//控制fork 行为
extern int pthread_equal(pthread_t __thread1,pthread_t __thread2);//线程相等
//线程私有数据
extern int pthread_key_create(pthread_key_t *__key,void(*__destr_function)(void *));
extern int pthread_key_delete(pthread_key_t __key);
extern void *pthread_getspecific(pthread_key_t __key);
extern int pthread_setspecific(pthread_key_t __key,const void *__pointer);
//_______________________________________________________________________________________________________________ */
#endif
int px_thread_get_rtaddr(pthread_t tid);
int px_thread_set_attr(pthread_attr_t *p_attr);
int px_thread_show_attr(pthread_attr_t *p_attr);
#define px_thread_attr_init(p_attr) ({\
	int ret=0;\
	ret=pthread_attr_init(p_attr);\
	if(ret)show_errno(ret,"pthread_attr_init");\
	ret=ret?-1:0;\
})
#define px_thread_exit(p_ret)  pthread_exit(p_ret)

#define px_thread_create(px_tid,p_attr,p_start_routine,args) ({\
	int ret=0;\
	ret=pthread_create(px_tid,p_attr,p_start_routine,args);\
	if(ret)show_errno(ret,"pthread_create");\
	ret=ret?-1:0;\
})
#define px_thread_set_cancel_state(state) ({\
	int ret=0;\
	ret=pthread_setcancelstate(state,NULL);\
	if(ret)show_errno(ret,"pthread_setcancelstate");\
	ret=ret?-1:0;\
})
#define px_thread_set_cancel_type(type) ({\
	int ret=0;\
	ret=pthread_setcanceltype(type,NULL);\
	if(ret)show_errno(ret,"pthread_setcanceltype");\
	ret=ret?-1:0;\
})
#define px_thread_cancel(px_tid) ({\
	int ret=0;\
	ret=pthread_cancel(px_tid);\
	if(ret)show_errno(ret,"px_thread_cancel");\
	ret=ret?-1:0;\
})
#define px_thread_yield() ({\
	int ret=0;\
	ret=pthread_yield();\
	if(ret)show_errno(ret,"px_thread_cancel");\
	ret=ret?-1:0;\
})
#define px_thread_join(tid,p_ret) ({\
	int ret=0;\
	ret=pthread_join(tid,p_ret);\
	if(ret)show_errno(ret,"pthread_join");\
	ret;\
})
#define px_thread_tryjoin(tid,p_ret) ({\
	int ret=0;\
	ret=pthread_tryjoin_np(tid,p_ret);\
	if(ret)show_errno(ret,"pthread_tryjoin_np");\
	ret=ret?-1:0;\
})
#define px_thread_timedjoin(tid,p_ret,p_ts) ({\
	int ret=0;\
	ret=pthread_timedjoin_np(tid,p_ret,p_ts);\
	if(ret)show_errno(ret,"pthread_join");\
	ret=ret?-1:0;\
})
#define px_thread_setschedparam(tid,policy,p_param) ({\
	int ret=0;\
	ret=pthread_setschedparam(tid,policy,p_param);\
	if(ret)show_errno(ret,"pthread_setschedparam");\
	ret=ret?-1:0;\
})
#define px_thread_setaffinity_np(tid,cpusetsize,p_cpuset) ({\
	int ret=0;\
	ret=pthread_setaffinity_np(tid,cpusetsize,p_cpuset);\
	if(ret)show_errno(ret,"pthread_setaffinity_np");\
	ret=ret?-1:0;\
})
#define px_thread_setschedprio(tid,prio) ({\
	int ret=0;\
	ret=pthread_setschedprio(tid,prio);\
	if(ret)show_errno(ret,"pthread_setschedprio");\
	ret=ret?-1:0;\
})
#define px_thread_setname_np(tid,name) ({\
	int ret=0;\
	ret=pthread_setname_np(tid,name);\
	if(ret)show_errno(ret,"pthread_setconcurrency");\
	ret=ret?-1:0;\
})
#define px_thread_setconcurrency(level) ({\
	int ret=0;\
	ret=pthread_setconcurrency(level);\
	if(ret)show_errno(ret,"pthread_setconcurrency");\
	ret=ret?-1:0;\
})
#define px_thread_detach(tid) ({\
	int ret=0;\
	ret=pthread_detach(tid);\
	if(ret)show_errno(ret,"pthread_detach");\
	ret=ret?-1:0;\
})
#define px_thread_once(p_once_control,p_init_routine) ({\
	int ret=0;\
	ret=pthread_once(p_once_control,p_init_routine);\
	if(ret)show_errno(ret,"pthread_once");\
	ret=ret?-1:0;\
})
#define px_thread_atfork(p_prepare,p_parent,p_child) ({\
	int ret=0;\
	ret=pthread_atfork(p_prepare,p_parent,p_child);\
	if(ret)show_errno(ret,"pthread_atfork");\
	ret=ret?-1:0;\
})
#define px_thread_equal(tid1,tid2) ({\
	int ret=0;\
	ret=pthread_equal(tid1,tid2);\
	if(ret)show_errno(ret,"pthread_equal");\
	ret=ret?-1:0;\
})
#define px_thread_key_create(p_key,p_destr_function) ({\
	int ret=0;\
	ret=pthread_key_create(p_key,p_destr_function);\
	if(ret)show_errno(ret,"pthread_key_create");\
	ret=ret?-1:0;\
})
#define px_thread_key_delete(key) ({\
	int ret=0;\
	ret=pthread_key_delete(key);\
	if(ret)show_errno(ret,"pthread_key_delete");\
	ret=ret?-1:0;\
})
#define px_thread_getspecific(p_val,key) ({\
	int ret=0;\
	p_val=pthread_getspecific(key);\
	ret=p_val?0:-1;\
})
#define px_thread_setspecific(key,p_pointer) ({\
	int ret=0;\
	ret=pthread_setspecific(key,p_pointer);\
	if(ret)show_errno(ret,"pthread_setspecific");\
	ret=ret?-1:0;\
})
#define px_thread_attr_destroy(p_attr) ({\
	int ret=0;\
	ret=pthread_attr_destroy(p_attr);\
	if(ret)show_errno(ret,"pthread_attr_destroy");\
	ret=ret?-1:0;\
})
#endif