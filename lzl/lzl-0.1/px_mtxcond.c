#include <stdlib.h>
#include <sys/types.h>
#include "px_mtxcond.h"
#include "misc.h"
#include "px_cond.h"
#include "px_mutex.h"

int px_mtxcondattr_init(px_mtxcondattr_t *p_attr)
{
	px_condattr_init(&p_attr->condattr);
	px_mutexattr_init(&p_attr->mutexattr);
	return 0;
}
int px_mtxcondattr_destroy(px_mtxcondattr_t *p_attr)
{
	px_condattr_destroy(&p_attr->condattr);
	px_mutexattr_destroy(&p_attr->mutexattr);
	return 0;	
}
int px_mtxcond_init(px_mtxcond_t *p_mtxcond,px_mtxcondattr_t *p_attr)
{
	px_cond_init(&p_mtxcond->cond,p_attr?&p_attr->condattr:NULL);
	px_mutex_init(&p_mtxcond->mutex,p_attr?&p_attr->mutexattr:NULL);
	return 0;	
}
int px_mtxcond_destroy(px_mtxcond_t *p_mtxcond)
{
	px_cond_destroy(&p_mtxcond->cond);
	px_mutex_destroy(&p_mtxcond->mutex);
	return 0;
}
int px_mtxcond_signal(px_mtxcond_t *p_mtxcond)
{
	px_mutex_lock(&p_mtxcond->mutex);
	px_cond_signal(&p_mtxcond->cond);
	px_mutex_unlock(&p_mtxcond->mutex);
	return 0;
}
int px_mtxcond_broadcast(px_mtxcond_t *p_mtxcond)
{
	px_mutex_lock(&p_mtxcond->mutex);
	px_cond_broadcast(&p_mtxcond->cond);
	px_mutex_unlock(&p_mtxcond->mutex);
	return 0;
}
int px_mtxcond_wait(px_mtxcond_t *p_mtxcond)
{
	px_mutex_lock(&p_mtxcond->mutex);
	px_cond_wait(&p_mtxcond->cond,&p_mtxcond->mutex);
	px_mutex_unlock(&p_mtxcond->mutex);
	return 0;
}
int px_mtxcond_tdwait(px_mtxcond_t *p_mtxcond,const struct timespec *p_ts)
{
	px_mutex_lock(&p_mtxcond->mutex);
	px_cond_tdwait(&p_mtxcond->cond,&p_mtxcond->mutex,p_ts);
	px_mutex_unlock(&p_mtxcond->mutex);
	return 0;
}
int px_mtxcondattr_show(px_mtxcondattr_t *p_attr)
{
	px_condattr_show(&p_attr->condattr);
	px_mutexattr_show(&p_attr->mutexattr);
	return 0;
}
int px_mtxcondattr_set(px_mtxcondattr_t *p_attr)
{
	px_condattr_set(&p_attr->condattr);
	px_mutexattr_set(&p_attr->mutexattr);
	return 0;
}