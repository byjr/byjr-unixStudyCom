#ifndef _PX_SPIN_LOCK_H
#define _PX_SPIN_LOCK_H 1
//  ____________________________________________________________________________
extern int pthread_spin_destroy(pthread_spinlock_t *__lock);
extern int pthread_spin_init(pthread_spinlock_t *__lock,int __pshared);
extern int pthread_spin_lock(pthread_spinlock_t *__lock);
extern int pthread_spinlock_trylock(pthread_spinlock_t *__lock);
extern int pthread_spin_unlock(pthread_spinlock_t *__lock);
// ____________________________________________________________________________ */
#define SIG_CS_CMD SIGRTMIN
#define px_spin_destroy(p_lock) ({\
	int ret=0;\
	ret=pthread_spin_destroy(p_lock);\
	if(ret){\
		show_errno(ret,"pthread_spin_destroy");\
		exit(-1);\
	}\
})
#define px_spin_init(p_lock,pshared) ({\
	int ret=0;\
	ret=pthread_spin_init(p_lock,pshared);\
	if(ret){\
		show_errno(ret,"pthread_spin_init");\
		exit(-1);\
	}\
})
#define px_spin_lock(p_lock) ({\
	int ret=0;\
	ret=pthread_spin_lock(p_lock);\
	if(ret){\
		show_errno(ret,"pthread_spin_lock");\
		exit(-1);\
	}\
})
#define px_spin_trylock(p_lock) ({\
	int ret=0;\
	ret=pthread_spinlock_trylock(p_lock);\
	ret=ret?-1:0;\
})
#define px_spin_unlock(p_lock) ({\
	int ret=0;\
	ret=pthread_spin_unlock(p_lock);\
	if(ret){\
		show_errno(ret,"pthread_spin_unlock");\
		exit(-1);\
	}\
})
#endif