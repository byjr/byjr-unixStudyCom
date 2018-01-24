#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sched.h>
#include "misc.h"
#include "slog.h"
#include "px_thread.h"

static void get_isset_bit(cpu_set_t cpuset){
	int i=0;
	inf("cpuset:");
	for(i=0;i<sizeof(cpuset)*8;i++){
		printf("%d",CPU_ISSET(i,&cpuset));
	}
	printf("\n");
}
int px_thread_show_attr(pthread_attr_t *p_attr)
{
	int ret, i;
	size_t v;
	void *stkaddr;
	struct sched_param sp;

//CPU亲缘性	
    cpu_set_t cpuset={0};
	ret = pthread_attr_getaffinity_np(p_attr,sizeof(cpu_set_t),&cpuset);
	if (ret){		
		show_errno(ret, "pthread_attr_getaffinity_np");
		return -1;
	}
	get_isset_bit(cpuset);
// 分离状态
	ret = pthread_attr_getdetachstate(p_attr, &i);
	if (ret){		
		show_errno(ret, "pthread_attr_getdetachstate");
		return -1;
	}
	inf("Detach state        =%s",
		(i == PTHREAD_CREATE_DETACHED) ? " 分离运行" :
		(i == PTHREAD_CREATE_JOINABLE) ? " 关联运行" :
		"???");
// 作用域
	ret = pthread_attr_getscope(p_attr, &i);
	if (ret){		
	   show_errno(ret, "pthread_attr_getscope");
		return -1;
	}
	inf("Scope               =%s",
		   (i == PTHREAD_SCOPE_SYSTEM)  ? " 系统范围" :
		   (i == PTHREAD_SCOPE_PROCESS) ? " 进程范围" :
		   "???");
// 是否继承
	ret = pthread_attr_getinheritsched(p_attr, &i);
	if (ret){		
	   show_errno(ret, "pthread_attr_getinheritsched");
		return -1;
	}
	inf("Inherit scheduler   = %s",
		   (i == PTHREAD_INHERIT_SCHED)  ? "继承调度" :
		   (i == PTHREAD_EXPLICIT_SCHED) ? "独立调度" :
		   "???");
// 调度策略
	ret = pthread_attr_getschedpolicy(p_attr, &i);
	if (ret){		
	   show_errno(ret, "pthread_attr_getschedpolicy");
		return -1;
	}
	inf("Scheduling policy   = %s",
		   (i == SCHED_OTHER) ? "分时" :
		   (i == SCHED_FIFO)  ? "FIFO" :
		   (i == SCHED_RR)    ? "实时" :
		   "???");
// 调度参数
	ret = pthread_attr_getschedparam(p_attr, &sp);
	if (ret){		
	   show_errno(ret, "pthread_attr_getschedparam");
		return -1;
	}
	inf("Scheduling priority = %d",  sp.sched_priority);
// 栈保护区大小
	ret = pthread_attr_getguardsize(p_attr, &v);
	if (ret){		
	   show_errno(ret, "pthread_attr_getguardsize");
		return -1;
	}
	inf("Guard size          = %d bytes",  (int)v);

// 程堆栈区
	ret = pthread_attr_getstack(p_attr, &stkaddr, &v);
	if (ret){		
	   show_errno(ret, "pthread_attr_getstack");
		return -1;
	}
	inf("Stack address       = 0x%016x",stkaddr);
	inf("Stack size          = %d bytes",(int)v);	
	return 0;
}
int px_thread_set_attr(pthread_attr_t *p_attr)
{
	int s=0;
	// cpu_set_t cpuset={0};	
	// CPU_SET(1,&cpuset);CPU_SET(0,&cpuset);
	// s = pthread_attr_setaffinity_np(p_attr,sizeof(cpu_set_t),&cpuset);
	// if (s){		
		// show_errno(s, "pthread_attr_getaffinity_np");
		// return -1;
	// }	
	// s = pthread_attr_setdetachstate(p_attr, PTHREAD_CREATE_DETACHED);
	// if (s != 0){		
		// show_errno(s, "pthread_attr_setdetachstate");
		// return -1;
	// }
	// s = pthread_attr_setscope(p_attr,PTHREAD_SCOPE_SYSTEM);
	// if (s != 0){		
		// show_errno(s, "pthread_attr_setscope");
		// return -1;
	// }
	s = pthread_attr_setinheritsched(p_attr, PTHREAD_EXPLICIT_SCHED);
	if (s != 0){		
		show_errno(s, "pthread_attr_setinheritsched");
		return -1;
	}
	s = pthread_attr_setschedpolicy(p_attr,SCHED_RR);
	if (s != 0){
		show_errno(s, "pthread_attr_setschedpolicy");
		return -1;		
	}		
	const struct sched_param param={51};
	s = pthread_attr_setschedparam(p_attr,&param);
	if (s != 0){
		show_errno(s, "pthread_attr_setschedparam");
		return -1;		
	}
	// s = pthread_attr_setguardsize(p_attr,PTHREAD_STACK_MIN/2);
	// if (s){		
	   // show_errno(s, "pthread_attr_getguardsize");
		// return -1;
	// }
	// void *stkaddr=NULL;
	// s = pthread_attr_setstack(p_attr, &stkaddr,PTHREAD_STACK_MIN);
	// if (s){		
	   // show_errno(s, "pthread_attr_getstack");
		// return -1;
	// }
	px_thread_show_attr(p_attr);
	return 0;
}
int px_thread_get_rtaddr(pthread_t tid)
{
	int ret=0;
	pthread_attr_t attr={0};
	ret=pthread_getattr_np(tid,&attr);
	if(ret){
		show_errno(ret,"pthread_getattr_np");
		return -1;	
	}
	ret=px_thread_show_attr(&attr);
	if(ret){
		show_error(ret,"px_thread_show_attr");
	}
	return 0;
}



