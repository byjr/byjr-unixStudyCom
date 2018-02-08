#ifndef _THREADPOOL_H
#define _THREADPOOL_H 1
#include <lzl/px_cond.h>
#include <lzl/px_mutex.h>
typedef void *(*tp_task_func_t)(void *args);
typedef struct tp_thread_t{
	struct tp_thread_t *next;
	pthread_t tid;
}tp_thread_t;
typedef struct tp_task_t{
	struct tp_task_t *next;
	tp_task_func_t func;
	void *args;
}tp_task_t;
typedef struct threadpool_t{
	tp_task_t *task_tbl_head;	//任务表 
	int cur_task_count;		
	int max_task_count;
	tp_task_t *task_tbl_tail;
	pthread_mutex_t	tp_mtx;
	pthread_cond_t tp_cond;
	pthread_attr_t thread_attr;		
	tp_thread_t *trd_tbl;	//线程表
	char destory_flag;
}threadpool_t;

#endif /* _THREADPOOL_H_ */
