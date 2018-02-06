#ifndef _UN_BARRIER_H
#define _UN_BARRIER_H 1
#include <stdlib.h>
//  ____________________________________________________________________________
extern int pthread_barrierattr_init(pthread_barrierattr_t *__attr);
extern int pthread_barrierattr_destroy(pthread_barrierattr_t *__attr);
extern int pthread_barrierattr_getpshared(const pthread_barrierattr_t *__attr,int *__pshared);
extern int pthread_barrierattr_setpshared(pthread_barrierattr_t *__attr,int __pshared);
extern int pthread_barrier_init(pthread_barrier_t *__barrier,const pthread_barrierattr_t *__attr,unsigned int __count);
extern int pthread_barrier_destroy(pthread_barrier_t *__barrier);
extern int pthread_barrier_wait(pthread_barrier_t *__barrier);
// ____________________________________________________________________________ */
extern int px_barrierattr_set(pthread_barrierattr_t *p_attr);
extern int px_barrierattr_show(pthread_barrierattr_t *p_attr);
#define SIG_CS_CMD SIGRTMIN
#define px_barrierattr_init(p_attr) {\
	int ret=0;\
	ret=pthread_barrierattr_init(p_attr);\
	if(ret){\
		show_errno(ret,"px_barrierattr_init");\
		exit(-1);\
	}\
}
#define px_barrierattr_destroy(p_attr) {\
	int ret=0;\
	ret=pthread_barrierattr_destroy(p_attr);\
	if(ret){\
		show_errno(ret,"px_barrierattr_destroy");\
		exit(-1);\
	}\
}
#define px_barrierattr_getpshared(p_attr,p_pshared) {\
	int ret=0;\
	ret=pthread_barrierattr_getpshared(p_attr,p_pshared);\
	if(ret){\
		show_errno(ret,"px_barrierattr_getpshared");\
		exit(-1);\
	}\
}
#define px_barrierattr_setpshared(p_attr,pshared) {\
	int ret=0;\
	ret=pthread_barrierattr_setpshared(p_attr,pshared);\
	if(ret){\
		show_errno(ret,"px_barrierattr_setpshared");\
		exit(-1);\
	}\
}
#define px_barrier_init(p_barrier,p_attr,count) {\
	int ret=0;\
	ret=pthread_barrier_init(p_barrier,p_attr,count);\
	if(ret)show_errno(ret,"px_barrier_init");\
	ret?-1:0;\
}
#define px_barrier_destroy(p_barrier) {\
	int ret=0;\
	ret=pthread_barrier_destroy(p_barrier);\
	if(ret){\
		show_errno(ret,"px_barrier_destroy");\
		exit(-1);\
	}\
}
#define px_barrier_wait(p_barrier) {\
	int ret=0;\
	ret=pthread_barrier_wait(p_barrier);\
	if(ret && ret!=PTHREAD_BARRIER_SERIAL_THREAD){\
		show_errno(ret,"px_barrier_wait");\
		exit(-1);\
	}\
}

#endif