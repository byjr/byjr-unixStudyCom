#ifndef _PX_MTXCOND_H
#define _PX_MTXCOND_H 1
typedef struct px_mtxcond_t{
	pthread_cond_t cond;
	pthread_mutex_t mutex;	
}px_mtxcond_t;
typedef struct px_mtxcondattr_t{
	pthread_condattr_t condattr;
	pthread_mutexattr_t mutexattr;
}px_mtxcondattr_t;
int px_mtxcondattr_init(px_mtxcondattr_t *p_attr);
int px_mtxcondattr_destroy(px_mtxcondattr_t *p_attr);
int px_mtxcond_init(px_mtxcond_t *p_mtxcond,px_mtxcondattr_t *p_attr);
int px_mtxcond_destroy(px_mtxcond_t *p_mtxcond);
int px_mtxcond_signal(px_mtxcond_t *p_mtxcond);
int px_mtxcond_signal(px_mtxcond_t *p_mtxcond);
int px_mtxcond_broadcast(px_mtxcond_t *p_mtxcond);
int px_mtxcond_wait(px_mtxcond_t *p_mtxcond);
int px_mtxcond_tdwait(px_mtxcond_t *p_mtxcond,const struct timespec *p_ts);
#endif