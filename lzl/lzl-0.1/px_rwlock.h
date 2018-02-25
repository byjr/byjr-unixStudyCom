#ifndef _UN_RWLOCK_H
#define _UN_RWLOCK_H 1
/*//  ____________________________________________________________________________
extern int pthread_rwlockattr_init(pthread_rwlockattr_t *__attr);
extern int pthread_rwlockattr_destroy(pthread_rwlockattr_t *__attr);
 
extern int pthread_rwlockattr_getkind_np(const pthread_rwlockattr_t *__attr,int *__pref);
extern int pthread_rwlockattr_setkind_np(pthread_rwlockattr_t *__attr,int __pref);
extern int pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *__attr,int *__pshared);
extern int pthread_rwlockattr_setpshared(pthread_rwlockattr_t *__attr,int __pshared);

extern int pthread_rwlock_destroy(pthread_rwlock_t *__rwlock);
extern int pthread_rwlock_init(pthread_rwlock_t *__rwlock,const pthread_rwlockattr_t *__attr);

extern int pthread_rwlock_rdlock(pthread_rwlock_t *__rwlock);
extern int pthread_rwlock_tryrdlock(pthread_rwlock_t *__rwlock);
extern int pthread_rwlock_timedrdlock(pthread_rwlock_t *__rwlock,const struct timespec *__abstime);

extern int pthread_rwlock_wrlock(pthread_rwlock_t *__rwlock);
extern int pthread_rwlock_trywrlock(pthread_rwlock_t *__rwlock);
extern int pthread_rwlock_timedwrlock(pthread_rwlock_t *__rwlock,const struct timespec *__abstime);

extern int pthread_rwlock_unlock(pthread_rwlock_t *__rwlock);
// ____________________________________________________________________________ */
extern int px_rwlockattr_set(pthread_rwlockattr_t *p_attr);
extern int px_rwlockattr_show(pthread_rwlockattr_t *p_attr);
#define SIG_CS_CMD SIGRTMIN

#define px_rwlockattr_init(p_rwlockattr) ({\
	int ret=0;\
	ret=pthread_rwlockattr_init(p_rwlockattr);\
	if(ret){\
		show_errno(ret,"px_rwlockattr_init");\
		exit(-1);\
	}\
})
#define px_rwlockattr_destroy(p_rwlockattr) ({\
	int ret=0;\
	ret=pthread_rwlockattr_destroy(p_rwlockattr);\
	if(ret){\
		show_errno(ret,"px_rwlockattr_destroy");\
		exit(-1);\
	}\
})
#define px_rwlock_init(p_rwlock,p_rwlockattr) ({\
	int ret=0;\
	ret=pthread_rwlock_init(p_rwlock,p_rwlockattr);\
	if(ret){\
		show_errno(ret,"pthread_rwlock_init");\
		exit(-1);\
	}\
})
#define px_rwlock_destroy(p_rwlock) ({\
	int ret=0;\
	ret=pthread_rwlock_destroy(p_rwlock);\
	if(ret){\
		show_errno(ret,"pthread_rwlock_init");\
		exit(-1);\
	}\
})

#define px_rwlock_rdlock(p_rwlock) ({\
	int ret=0;\
	ret=pthread_rwlock_rdlock(p_rwlock);\
	if(ret){\
		show_errno(ret,"pthread_rwlock_rdlock");\
		exit(-1);\
	}\
})
#define px_rwlock_tryrdlock(p_rwlock) ({\
	int ret=0;\
	ret=pthread_rwlock_tryrdlock(p_rwlock);\
	ret=ret?-1:0;\
})
#define px_rwlock_timedrdlock(p_rwlock,p_abstime) ({\
	int ret=0;\
	ret=pthread_rwlock_timedrdlock(p_rwlock,p_abstime);\
	ret=ret?-1:0;\
})

#define px_rwlock_wrlock(p_rwlock) ({\
	int ret=0;\
	ret=pthread_rwlock_wrlock(p_rwlock);\
	if(ret){\
		show_errno(ret,"pthread_rwlock_wrlock");\
		exit(-1);\
	}\
})
#define px_rwlock_trywrlock(p_rwlock) ({\
	int ret=0;\
	ret=pthread_rwlock_trywrlock(p_rwlock);\
	ret=ret?-1:0;\
})
#define px_rwlock_timedwrlock(p_rwlock,p_abstime) ({\
	int ret=0;\
	ret=pthread_rwlock_timedwrlock(p_rwlock,p_abstime);\
	ret=ret?-1:0;\
})
#define px_rwlock_unlock(p_rwlock) ({\
	int ret=0;\
	ret=pthread_rwlock_unlock(p_rwlock);\
	if(ret){\
		show_errno(ret,"pthread_rwlock_unlock");\
		exit(-1);\
	}\
})
#endif