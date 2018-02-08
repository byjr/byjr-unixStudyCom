#ifndef PX_MSGQ_H_
#define PX_MSGQ_H_ 1
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include "lzl/misc.h"
#include "lzl/slog.h"

int px_msgq_showattr(struct mq_attr *p_attr);
int mq_unlink(const char *name);//删除链接数
int mq_close(mqd_t mqdes);

#ifndef PX_MQ_MAXMSG_COUNT
#define PX_MQ_MAXMSG_COUNT 8
#endif

#ifndef PX_MQ_MSGSIZE
#define PX_MQ_MSGSIZE 100
#endif 

#define px_msgq_getattr(p_attr,mqdes) ({\
	int	ret=mq_getattr(mqdes,p_attr);\
	if(-1==ret) show_error(ret,"px_msgq_getattr");\
	ret?-1:0;\
})

#define px_msgq_open(name){\
	struct mq_attr attr={\
		.mq_maxmsg	=PX_MQ_MAXMSG_COUNT,\
		.mq_msgsize	=PX_MQ_MSGSIZE,\
	};\
	mqd_t mqd=mq_open(name,O_CREAT|O_RDWR,S_IRUSR|S_IWUSR,&attr);\
	if((mqd_t)-1==mqd) {\
		show_error(0,"mq_open");\
	}\
	mqd;\
}

#define  px_msgq_send(mqdes,msg_ptr,msg_prio) ({\
	int ret=mq_send(mqdes,msg_ptr,PX_MQ_MSGSIZE,msg_prio);\
	if(-1==ret)show_error(0,"px_msgq_send");\
	ret?-1:0;\
})

#define  px_msgq_timedsend(mqdes,msg_ptr,msg_prio,tsv) ({\
	struct timespec ts={0};\
	int ret=clock_gettime(CLOCK_REALTIME, &ts);\
	ts.tv_sec+=(tsv).tv_sec;\
	ts.tv_nsec+=(tsv).tv_nsec;\
	if(-1 == ret){\
		show_error(0,"clock_gettime");\
	}\
	ret=mq_timedsend(mqdes,msg_ptr,PX_MQ_MSGSIZE,msg_prio,&ts);\
	if(-1 == ret)show_error(0,"mq_timedsend");\
	ret?-1:0;\
})

#define px_msgq_receive(msg_ptr,mqdes,msg_prio) ({\
	int ret=mq_receive(mqdes,msg_ptr,PX_MQ_MSGSIZE,msg_prio);\
	if(-1 == ret)show_error(0,"px_msgq_receive");\
	ret?-1:0;\
})

#define px_msgq_timedreceive(msg_ptr,mqdes,msg_prio,tsv) ({\
	struct timespec ts={0};\
	int ret=clock_gettime(CLOCK_REALTIME, &ts);\
	ts.tv_sec+=(tsv).tv_sec;\
	ts.tv_nsec+=(tsv).tv_nsec;\
	if(-1 == ret){\
		show_error(0,"clock_gettime");\
	}\
	ret=mq_timedreceive(mqdes,msg_ptr,PX_MQ_MSGSIZE,msg_prio,&ts);\
	if(-1 == ret)show_error(0,"px_msgq_timedreceive");\
	ret?-1:0;\
})

#define px_msgq_notify(mqdes,p_sevp) ({\
	int ret=mq_notify(mqdes,p_sevp);\
	if(-1 == ret)show_error(0,"px_msgq_notify");\
	ret?-1:0;\
})

#endif