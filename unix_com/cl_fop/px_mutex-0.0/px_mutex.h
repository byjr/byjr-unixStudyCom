#ifndef _UN_MUTEX_H
#define _UN_MUTEX_H 1
//  ____________________________________________________________________________
extern int pthread_mutex_consistent(pthread_mutex_t *__mutex);
extern int pthread_mutex_destroy(pthread_mutex_t *__mutex);
extern int pthread_mutex_getprioceiling(const pthread_mutex_t *__mutex,int *__prioceiling);
extern int pthread_mutex_init(pthread_mutex_t *__mutex,const pthread_mutexattr_t *__mutexattr);
extern int pthread_mutex_lock(pthread_mutex_t *__mutex);
extern int pthread_mutex_setprioceiling(pthread_mutex_t *__mutex,int __prioceiling,int *__old_ceiling);
extern int pthread_mutex_timedlock(pthread_mutex_t *__mutex,const struct timespec *__abstime);
extern int pthread_mutex_trylock(pthread_mutex_t *__mutex);
extern int pthread_mutex_unlock(pthread_mutex_t *__mutex);
extern int pthread_mutexattr_destroy(pthread_mutexattr_t *__attr);
extern int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *__attr,int *__prioceiling);
extern int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *__attr,int *__protocol);
extern int pthread_mutexattr_getpshared(const pthread_mutexattr_t *__attr,int *__pshared);
extern int pthread_mutexattr_getrobust(const pthread_mutexattr_t *__attr,int *__robustness);
extern int pthread_mutexattr_gettype(const pthread_mutexattr_t *__attr,int *__kind);
extern int pthread_mutexattr_init(pthread_mutexattr_t *__attr);
extern int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *__attr,int __prioceiling);
extern int pthread_mutexattr_setprotocol(pthread_mutexattr_t *__attr,int __protocol);
extern int pthread_mutexattr_setpshared(pthread_mutexattr_t *__attr,int __pshared);
extern int pthread_mutexattr_setrobust(pthread_mutexattr_t *__attr,int __robustness);
extern int pthread_mutexattr_settype(pthread_mutexattr_t *__attr,int __kind);
// ____________________________________________________________________________ 
extern int px_mutexattr_set(pthread_mutexattr_t *p_attr);
extern int px_mutexattr_show(pthread_mutexattr_t *p_attr);
#define SIG_CS_CMD SIGRTMIN
#define px_thread_mutexattr_init(p_attr) ({\
	int ret=0;\
	ret=pthread_mutexattr_init(p_attr);\
	if(ret)show_errno(ret,"pthread_mutexattr_init");\
	ret?-1:0;\
})
#define px_thread_mutexattr_destroy(p_attr) ({\
	int ret=0;\
	ret=pthread_mutexattr_destroy(p_attr);\
	if(ret){\
		show_errno(ret,"pthread_mutexattr_destroy");\
		exit(-1);\
	}\
})
#define px_thread_mutexattr_getprioceiling(p_attr,p_prioceiling) ({\
	int ret=0;\
	ret=pthread_mutexattr_getprioceiling(p_attr,p_prioceiling);\
	if(ret)show_errno(ret,"pthread_mutexattr_getprioceiling");\
	ret?-1:0;\
})
#define px_thread_mutexattr_getprotocol(p_attr,p_protocol) ({\
	int ret=0;\
	ret=pthread_mutexattr_getprotocol(p_attr,p_protocol);\
	if(ret)show_errno(ret,"pthread_mutexattr_getprotocol");\
	ret?-1:0;\
})

#define px_thread_mutexattr_getpshared(p_attr,p_pshared) ({\
	int ret=0;\
	ret=pthread_mutexattr_getpshared(p_attr,p_pshared);\
	if(ret)show_errno(ret,"pthread_mutexattr_getpshared");\
	ret?-1:0;\
})
#define px_thread_mutexattr_getrobust(p_attr,p_robustness) ({\
	int ret=0;\
	ret=pthread_mutexattr_getrobust(p_attr,p_robustness);\
	if(ret)show_errno(ret,"pthread_mutexattr_getrobust");\
	ret?-1:0;\
})
#define px_thread_mutexattr_gettype(p_attr,p_kind) ({\
	int ret=0;\
	ret=pthread_mutexattr_gettype(p_attr,p_kind);\
	if(ret)show_errno(ret,"pthread_mutexattr_gettype");\
	ret?-1:0;\
})

#define px_thread_mutexattr_setprioceiling(p_attr,prioceiling) ({\
	int ret=0;\
	ret=pthread_mutexattr_setprioceiling(p_attr,prioceiling);\
	if(ret)show_errno(ret,"pthread_mutexattr_setprioceiling");\
	ret?-1:0;\
})

#define px_thread_mutexattr_setprotocol(p_attr,protocol) ({\
	int ret=0;\
	ret=pthread_mutexattr_setprotocol(p_attr,protocol);\
	if(ret)show_errno(ret,"pthread_mutexattr_setprotocol");\
	ret?-1:0;\
})

#define px_thread_mutexattr_setpshared(p_attr,pshared) ({\
	int ret=0;\
	ret=pthread_mutexattr_setpshared(p_attr,pshared);\
	if(ret)show_errno(ret,"pthread_mutexattr_setpshared");\
	ret?-1:0;\
})

#define px_thread_mutexattr_setrobust(p_attr,robustness) ({\
	int ret=0;\
	ret=pthread_mutexattr_setrobust(p_attr,robustness);\
	if(ret)show_errno(ret,"pthread_mutexattr_setrobust");\
	ret?-1:0;\
})

#define px_thread_mutexattr_settype(p_attr,kind) ({\
	int ret=0;\
	ret=pthread_mutexattr_settype(p_attr,kind);\
	if(ret)show_errno(ret,"pthread_mutexattr_settype");\
	ret?-1:0;\
})


#define px_mutex_init(p_mutex,p_mutexattr) ({\
	int ret=0;\
	ret=pthread_mutex_init(p_mutex,p_mutexattr);\
	if(ret)show_errno(ret,"pthread_mutex_init");\
	ret?-1:0;\
})

#define px_mutex_destroy(p_mutex) ({\
	int ret=0;\
	ret=pthread_mutex_destroy(p_mutex);\
	if(ret){\
		show_errno(ret,"pthread_mutex_destroy");\
		exit(-1);\
	}\
})




#define px_mutex_getprioceiling(p_mutex,p_prioceiling) ({\
	int ret=0;\
	ret=pthread_mutex_getprioceiling(p_mutex,p_prioceiling);\
	if(ret)show_errno(ret,"pthread_mutex_getprioceiling");\
	ret?-1:0;\
})

#define px_mutex_setprioceiling(p_mutex,prioceiling,p_old_ceiling) ({\
	int ret=0;\
	ret=pthread_mutex_setprioceiling(p_mutex,prioceiling,p_old_ceiling);\
	if(ret)show_errno(ret,"pthread_mutex_setprioceiling");\
	ret?-1:0;\
})

#define px_mutex_consistent(p_mutex) ({\
	int ret=0;\
	ret=pthread_mutex_consistent(p_mutex);\
	if(ret)show_errno(ret,"pthread_mutex_consistent");\
	ret?-1:0;\
})


#define px_mutex_lock(p_mutex) ({\
	int ret=0;\
	ret=pthread_mutex_lock(p_mutex);\
	if(ret)show_errno(ret,"pthread_mutex_lock");\
	ret?-1:0;\
})

#define px_mutex_trylock(p_mutex) ({\
	int ret=0;\
	ret=pthread_mutex_trylock(p_mutex);\
	ret=ret?-1:0;\
})

#define px_mutex_timedlock(p_abstime) ({\
	int ret=0;\
	ret=pthread_mutex_timedlock(p_abstime);\
	ret=ret?-1:0;\
})

#define px_mutex_unlock(p_mutex) ({\
	int ret=0;\
	ret=pthread_mutex_unlock(p_mutex);\
	if(ret)show_errno(ret,"pthread_mutex_unlock");\
	ret?-1:0;\
})
#endif