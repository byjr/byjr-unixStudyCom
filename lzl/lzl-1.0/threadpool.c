#include "threadpool.h"
#include <limits.h>
#include "px_thread.h"
static void *tp_star_routine(void *args){
	int ret=0;
	threadpool_t *p_tp=(threadpool_t *)args;
	rb_unit_t task={0};
	do{
		inf("thread %ld is ready...",pthread_self());
		px_mutex_lock(&(p_tp->tp_mtx));
		task.tid=pthread_self();
		task.flag=1;
		ret=rb_read(&task,p_tp->task_rb);
		do{
			if(!ret || p_tp->destory_flag)break;
			px_thread_cond_wait(&(p_tp->tp_cond),&(p_tp->tp_mtx));
			task.flag=2;
			task.tid=pthread_self();
			ret=rb_read(&task,p_tp->task_rb);
		// }while(0);
		}while(ret);
		if(p_tp->destory_flag){
			err("thread %ld is exit...",pthread_self());
			px_mutex_unlock(&(p_tp->tp_mtx));	
			return NULL;
		}
		// rb_flag_query(p_tp->task_rb);
		px_mutex_unlock(&(p_tp->tp_mtx));
		task.func(task.args);		
	}while(1);
}
int threadpool_task_add(threadpool_t *p_tp,tp_task_func_t func,void *args){
	int ret=0;
	rb_unit_t tp_task={1};
	tp_task.func=func;
	tp_task.args=args;
	px_mutex_lock(&(p_tp->tp_mtx));
	rb_write(p_tp->task_rb,&tp_task);
	// rb_flag_query(p_tp->task_rb);	
	px_thread_cond_signal(&(p_tp->tp_cond));
	px_mutex_unlock(&(p_tp->tp_mtx));
	return 0;
}
int tp_thread_set_attr(pthread_attr_t *p_attr){
	int s=0;
	// cpu_set_t cpuset={0};	
	// CPU_SET(1,&cpuset);CPU_SET(0,&cpuset);
	// s = pthread_attr_setaffinity_np(p_attr,sizeof(cpu_set_t),&cpuset);
	// if (s){		
		// show_errno(s, "pthread_attr_getaffinity_np");
		// exit(-1);
	// }	
	s = pthread_attr_setdetachstate(p_attr, PTHREAD_CREATE_DETACHED);
	if (s != 0){		
		show_errno(s, "pthread_attr_setdetachstate");
		exit(-1);
	}
	// s = pthread_attr_setscope(p_attr,PTHREAD_SCOPE_SYSTEM);
	// if (s != 0){		
		// show_errno(s, "pthread_attr_setscope");
		// exit(-1);
	// }
	// s = pthread_attr_setinheritsched(p_attr, PTHREAD_EXPLICIT_SCHED);
	// if (s != 0){		
		// show_errno(s, "pthread_attr_setinheritsched");
		// exit(-1);
	// }
	// s = pthread_attr_setschedpolicy(p_attr,SCHED_RR);
	// if (s != 0){
		// show_errno(s, "pthread_attr_setschedpolicy");
		// exit(-1);		
	// }		
	// const struct sched_param param={51};
	// s = pthread_attr_setschedparam(p_attr,&param);
	// if (s != 0){
		// show_errno(s, "pthread_attr_setschedparam");
		// exit(-1);		
	// }
	// s = pthread_attr_setguardsize(p_attr,PTHREAD_STACK_MIN);
	// if (s){		
	   // show_errno(s, "pthread_attr_getguardsize");
		// exit(-1);
	// }
	// s = pthread_attr_setstack(p_attr,NULL,4*PTHREAD_STACK_MIN);
	// if (s){		
		// show_errno(s, "pthread_attr_getstack");
		// exit(-1);
	// }
	s=pthread_attr_setstacksize(p_attr,4*PTHREAD_STACK_MIN);
	if (s){		
		show_errno(s, "pthread_attr_setstacksize");
		exit(-1);
	}	
	px_thread_show_attr(p_attr);
	return 0;
}
threadpool_t *threadpool_create(int max_trd,int max_task){
	int i=0,ret=0;
	threadpool_t *p_tp=NULL;
	p_tp=(threadpool_t *)calloc(1,sizeof(threadpool_t));
	if(!p_tp) exit(-1);
	px_mutex_init(&(p_tp->tp_mtx),NULL);
	px_thread_cond_init(&(p_tp->tp_cond),NULL);
	p_tp->task_rb=(ring_buf_t *)calloc(1,sizeof(ring_buf_t));
	if(!p_tp->task_rb) exit(-1);
	p_tp->task_rb->tbl=(rb_unit_t*)calloc(max_task,sizeof(rb_unit_t));
	if(!p_tp->task_rb->tbl) exit(-1);
	p_tp->task_rb->size=max_task;
	px_thread_attr_init(&(p_tp->thread_attr));
	// tp_thread_set_attr(&(p_tp->thread_attr));	
	pthread_t *trd_tbl=(pthread_t *)calloc(max_trd,sizeof(pthread_t));
	if(!trd_tbl) exit(-1);
	p_tp->max_trd_count=max_trd;
	for(i=0;i<max_trd;i++){
		px_thread_create(&trd_tbl[i],&(p_tp->thread_attr),tp_star_routine,p_tp);
	}
	p_tp->trd_tbl=trd_tbl;
	return p_tp;
}
int threadpool_destory(threadpool_t *p_tp){
	int i=0;
	px_mutex_lock(&(p_tp->tp_mtx));	
	p_tp->destory_flag=1;
	px_thread_cond_broadcast(&(p_tp->tp_cond));
	px_mutex_unlock(&(p_tp->tp_mtx));
	for(i=0;i<p_tp->max_trd_count;i++){
		px_thread_join(p_tp->trd_tbl[i],NULL);
		inf("thread %ld succeed exit!",p_tp->trd_tbl[i]);
	}
	free(p_tp->trd_tbl);
	free(p_tp->task_rb->tbl);
	free(p_tp->task_rb);	
	px_thread_attr_destroy(&(p_tp->thread_attr));
	px_thread_cond_destroy(&(p_tp->tp_cond));
	px_mutex_destroy(&(p_tp->tp_mtx));
	FREE(p_tp);
	return 0;
}

