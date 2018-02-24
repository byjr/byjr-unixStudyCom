#ifndef _PX_COND_H
#define _PX_COND_H 1
//  ____________________________________________________________________________
extern int pthread_condattr_init(pthread_condattr_t *__attr);
extern int pthread_condattr_destroy(pthread_condattr_t *__attr);
extern int pthread_condattr_getclock(const pthread_condattr_t *__attr,__clockid_t *__clock_id);
extern int pthread_condattr_setclock(pthread_condattr_t *__attr,__clockid_t __clock_id);
extern int pthread_condattr_getpshared(const pthread_condattr_t *__attr,int *__pshared);
extern int pthread_condattr_setpshared(pthread_condattr_t *__attr,int __pshared);
extern int pthread_cond_destroy(pthread_cond_t *__cond);
extern int pthread_cond_init(pthread_cond_t *__cond,const pthread_condattr_t *__cond_attr);
extern int pthread_cond_signal(pthread_cond_t *__cond);
extern int pthread_cond_broadcast(pthread_cond_t *__cond);
extern int pthread_cond_timedwait(pthread_cond_t *__cond,pthread_mutex_t *__mutex,const struct timespec *__abstime);
extern int pthread_cond_wait(pthread_cond_t *__cond,pthread_mutex_t *__mutex);//等待条件并解锁
// ____________________________________________________________________________ 
extern int px_condattr_set(pthread_condattr_t *p_attr);
extern int px_condattr_show(pthread_condattr_t *p_attr);
#define px_cond_broadcast(p_cond) ({\
	int ret=0;\
	ret=pthread_cond_broadcast(p_cond);\
	if(ret)show_errno(ret,"pthread_cond_broadcast");\
	ret?-1:0;\
})
#define px_cond_destroy(p_cond) ({\
	int ret=0;\
	ret=pthread_cond_destroy(p_cond);\
	if(ret)show_errno(ret,"pthread_cond_destroy");\
	ret?-1:0;\
})
#define px_cond_init(p_cond,p_cond_attr) ({\
	int ret=0;\
	ret=pthread_cond_init(p_cond,p_cond_attr);\
	if(ret)show_errno(ret,"pthread_cond_init");\
	ret?-1:0;\
})
#define px_cond_signal(p_cond) ({\
	int ret=0;\
	ret=pthread_cond_signal(p_cond);\
	if(ret)show_errno(ret,"pthread_cond_signal");\
	ret?-1:0;\
})
#define px_cond_tdwait(p_cond,p_mutex,p_ntv) ({\
	int ret=0;\
	ret=pthread_cond_timedwait(p_cond,p_mutex,p_ntv);\
	ret=ret?-1:0;\
})
#define px_cond_wait(p_cond,p_mutex) ({\
	int ret=0;\
	ret=pthread_cond_wait(p_cond,p_mutex);\
	if(ret)show_errno(ret,"pthread_cond_wait");\
	ret?-1:0;\
})
#define px_condattr_destroy(p_attr) ({\
	int ret=0;\
	ret=pthread_condattr_destroy(p_attr);\
	if(ret)show_errno(ret,"pthread_condattr_destroy");\
	ret?-1:0;\
})
#define px_condattr_getclock(p_attr,cid) ({\
	int ret=0;\
	ret=pthread_condattr_getclock(p_attr,cid);\
	if(ret)show_errno(ret,"pthread_condattr_getclock");\
	ret?-1:0;\
})
#define px_condattr_getpshared(p_attr,pshared) ({\
	int ret=0;\
	ret=pthread_condattr_getpshared(p_attr,pshared);\
	if(ret)show_errno(ret,"pthread_condattr_getpshared");\
	ret?-1:0;\
})
#define px_condattr_init(p_attr) ({\
	int ret=0;\
	ret=pthread_condattr_init(p_attr);\
	if(ret)show_errno(ret,"pthread_condattr_init");\
	ret?-1:0;\
})
#define px_condattr_setclock(p_attr,cid) ({\
	int ret=0;\
	ret=pthread_condattr_setclock(p_attr,cid);\
	if(ret)show_errno(ret,"pthread_condattr_setclock");\
	ret?-1:0;\
})
#define px_condattr_setpshared(p_attr,pshared) ({\
	int ret=0;\
	ret=pthread_condattr_setpshared(p_attr,pshared);\
	if(ret)show_errno(ret,"pthread_condattr_setpshared");\
	ret?-1:0;\
})
#endif