#ifndef _THREADPOOL_H
#define _THREADPOOL_H 1
#include "px_cond.h"
#include "px_mutex.h"
#include "ring_buf.h"
typedef void *(*tp_task_func_t)(void *args);

typedef struct threadpool_t{
	ring_buf_t *task_rb;//任务循环buf
	pthread_t *trd_tbl;	//线程表
	char destory_flag;
	pthread_mutex_t	tp_mtx;
	int max_trd_count;
	pthread_cond_t tp_cond;
	pthread_attr_t thread_attr;
}threadpool_t;

static void *tp_star_routine(void *args);
int threadpool_task_add(threadpool_t *p_tp,tp_task_func_t func,void *args);
int tp_thread_set_attr(pthread_attr_t *p_attr);
int threadpool_destory(threadpool_t *p_tp);

#endif
