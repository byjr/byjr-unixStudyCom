#include "threadpool.h"
#include <lzl/px_thread.h>
#include <lzl/px_mutex.h>
static void *tp_star_routine(void *args){
	threadpool_t *p_tp=(threadpool_t *)args;
	tp_task_t task={0};
	do{
		dbg("thread %ld is ready...",pthread_self());
		px_mutex_lock(&p_tp->tp_mtx);
		// inf("task_tbl_head=0x%08x!",p_tp->task_tbl_head);
		if(p_tp->cur_task_count<=0 && (!p_tp->task_tbl_head)){
			inf("task_tbl_head is empty!");
			if(!p_tp->destory_flag){
				px_cond_wait(&p_tp->tp_cond,&p_tp->tp_mtx);
				inf("task_tbl_head=0x%08x!",p_tp->task_tbl_head);
			}
		}
		if(p_tp->destory_flag){
			err("thread %ld is exit...",pthread_self());
			px_mutex_unlock(&p_tp->tp_mtx);	
			return NULL;
		}		
		inf("task_tbl_head=0x%08x!",p_tp->task_tbl_head);
		inf("func=0x%08x!",p_tp->task_tbl_head->func);
		memcpy(&task,p_tp->task_tbl_head,sizeof(task));
		tp_task_t *task_tmp=NULL;		
		task_tmp=p_tp->task_tbl_head;
		p_tp->task_tbl_head=p_tp->task_tbl_head->next;
		FREE(task_tmp);
		p_tp->cur_task_count--;
		war("thread %ld FREE cur=%d...",pthread_self(),p_tp->cur_task_count);		
		px_mutex_unlock(&p_tp->tp_mtx);			
		task.func(task.args);
	}while(1);
	return NULL;
}
int threadpool_destory(threadpool_t *p_tp)
{
	tp_task_t *task_idx=NULL;
	tp_thread_t *trd_idx=NULL,*tmp_idx=NULL;
	if(!p_tp)return -1;
	px_mutex_lock(&p_tp->tp_mtx);
	p_tp->destory_flag=1;
	px_cond_broadcast(&p_tp->tp_cond);
	px_mutex_unlock(&p_tp->tp_mtx);
	for(trd_idx=p_tp->trd_tbl;trd_idx;trd_idx=trd_idx->next){
		
		px_thread_join(trd_idx->tid,NULL);
		inf("thread %ld succeed exit!",trd_idx->tid);		
		if(!trd_idx->next) break;		
	}
	for(trd_idx=p_tp->trd_tbl;trd_idx;trd_idx=tmp_idx){
		tmp_idx=trd_idx->next;
		free(trd_idx);
	}
	for(task_idx=p_tp->task_tbl_head;task_idx;task_idx=task_idx->next){
		free(task_idx);
		if(!task_idx->next) break;		
	}
	px_mutex_destroy(&p_tp->tp_mtx);
	px_cond_destroy(&p_tp->tp_cond);
	return 0;
}
int threadpool_task_add(threadpool_t *p_tp,tp_task_func_t func,void *args)
{
	int ret=0,fail=1;
	tp_task_t *new=NULL,*idx=NULL;
	if(!p_tp)return -1;
	px_mutex_lock(&p_tp->tp_mtx);
	if(p_tp->cur_task_count>=p_tp->max_task_count){
		// war("%s failure,threadpool is full",__func__);
		tp_task_t *task_tmp=NULL;		
		task_tmp=p_tp->task_tbl_head;
		p_tp->task_tbl_head=p_tp->task_tbl_head->next;
		FREE(task_tmp);
		p_tp->cur_task_count--;
		war("thread %ld FREE cur=%d...",pthread_self(),p_tp->cur_task_count);
	}
	new=(tp_task_t*)calloc(1,sizeof(tp_task_t));
	if(!new)goto Exit0;
	new->func=func;
	new->args=args;	
	if(!p_tp->cur_task_count){
		p_tp->task_tbl_head=new;
	}else{
		p_tp->task_tbl_tail->next=new;
	}
	p_tp->task_tbl_tail=new;
	p_tp->cur_task_count++;
	war("thread %ld ADD cur=%d...",pthread_self(),p_tp->cur_task_count);
	px_cond_signal(&p_tp->tp_cond);
	fail=0;
Exit0:
	px_mutex_unlock(&p_tp->tp_mtx);	
	if(fail)return -1;
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
int threadpool_create(threadpool_t *p_tp,int max_trd,int max_task_count)
{
	int i=0,ret=0;
	tp_thread_t *trd_new=NULL,*tail_trd=NULL;
	memset(p_tp,0,sizeof(threadpool_t));
	px_mutex_init(&p_tp->tp_mtx,NULL);
	px_thread_attr_init(&p_tp->thread_attr);
	// tp_thread_set_attr(&p_tp->thread_attr);
	px_cond_init(&p_tp->tp_cond,NULL);
	p_tp->max_task_count=max_task_count;
	for(i=0;i<max_trd;i++){
		trd_new=(tp_thread_t*)calloc(1,sizeof(tp_thread_t)); 
		if(!trd_new)return -1;
		px_thread_create(&trd_new->tid,&p_tp->thread_attr,tp_star_routine,p_tp);
		if(p_tp->trd_tbl){
			tail_trd->next=trd_new;
			tail_trd=trd_new;
		}else{
			p_tp->trd_tbl=tail_trd=trd_new;
		}
	}
	return 0;
}

