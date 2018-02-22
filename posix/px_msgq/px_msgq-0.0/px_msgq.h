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
#include "lzl/fifo_cmd.h"
#if 0
extern mqd_t mq_open (const char *__name, int __oflag, ...)
extern int mq_close (mqd_t __mqdes);
extern int mq_getattr (mqd_t __mqdes, struct mq_attr *__mqstat);
extern int mq_setattr(mqd_t mqdes, const struct mq_attr *newattr,
                        struct mq_attr *oldattr);
extern int mq_notify (mqd_t __mqdes, const struct sigevent *__notification);
			   extern ssize_t mq_receive (mqd_t __mqdes, char *__msg_ptr, size_t __msg_len,
			   unsigned int *__msg_prio);
extern int mq_send (mqd_t __mqdes, const char *__msg_ptr, size_t __msg_len,
		    unsigned int __msg_prio);
extern ssize_t mq_receive (mqd_t __mqdes, char *__msg_ptr, size_t __msg_len,
			   unsigned int *__msg_prio			
extern ssize_t mq_timedreceive (mqd_t __mqdes, char * __msg_ptr,
				size_t __msg_len,
				unsigned int * __msg_prio,
				const struct timespec * __abs_timeout);
extern int mq_timedsend (mqd_t __mqdes, const char *__msg_ptr,
			 size_t __msg_len, unsigned int __msg_prio,
			 const struct timespec *__abs_timeout);
#endif			 

extern int px_msgq_showattr(struct mq_attr *p_attr);
extern int mq_unlink(const char *name);//删除链接数
extern int mq_close(mqd_t mqdes);

#ifndef PX_MQ_MAXMSG_COUNT
#define PX_MQ_MAXMSG_COUNT 8
#endif

#ifndef PX_MQ_MSGSIZE
#define PX_MQ_MSGSIZE 100
#endif 

#define px_msgq_getattr(p_attr,mqdes) ({\
	int	ret=mq_getattr(mqdes,p_attr);\
	if(-1==ret) show_errno(ret,"px_msgq_getattr");\
	px_msgq_showattr(p_attr);\
	ret?-1:0;\
})

#define px_msgq_setattr(mqdes,p_attr) ({\
	int	ret=mq_setattr(mqdes,p_attr,NULL);\
	if(-1==ret) show_errno(ret,"px_msgq_getattr");\
	ret?-1:0;\
})

#define px_msgq_open(name) ({\
	struct mq_attr attr={\
		.mq_maxmsg	=PX_MQ_MAXMSG_COUNT,\
		.mq_msgsize	=PX_MQ_MSGSIZE,\
	};\
	mqd_t mqd=mq_open(name,O_CREAT|O_RDWR,S_IRUSR|S_IWUSR,&attr);\
	if((mqd_t)-1==mqd) {\
		show_errno(0,"mq_open");\
	}\
	mqd;\
})

#define  px_msgq_send(mqdes,msg_ptr,p_prio) ({\
	int ret=mq_send(mqdes,msg_ptr,PX_MQ_MSGSIZE,p_prio);\
	if(-1==ret)show_errno(0,"px_msgq_send");\
	ret?-1:0;\
})

#define  px_msgq_timedsend(mqdes,msg_ptr,prio,tsv) ({\
	struct timespec ts={0};\
	int ret=clock_gettime(CLOCK_REALTIME, &ts);\
	if(-1==ret)show_errno(0,"clock_gettime");\
	inf("sec=%012u,nsec=%012u",ts.tv_sec,ts.tv_nsec);\
	inf("sec=%012u,nsec=%012u",tsv.tv_sec,tsv.tv_nsec);\
	ts.tv_sec+=(tsv).tv_sec;\
	ts.tv_nsec+=(tsv).tv_nsec;\
	if(ts.tv_nsec>999999999){\
		ts.tv_sec+1;\
		ts.tv_nsec%=1000000000;\
	}\
	err("sec=%012u,nsec=%012u",ts.tv_sec,ts.tv_nsec);\
	war("mqdes=%d,msg_ptr=%s,PX_MQ_MSGSIZE:%u,prio:%d,ts:%016p",mqdes,msg_ptr,PX_MQ_MSGSIZE,prio,&ts)\
	ret=mq_timedsend(mqdes,msg_ptr,PX_MQ_MSGSIZE,prio,&ts);\
	if(-1 == ret)show_errno(0,"mq_timedsend");\
	ret?-1:0;\
})

#define px_msgq_receive(msg_ptr,mqdes,p_prio) ({\
	int ret=mq_receive(mqdes,msg_ptr,PX_MQ_MSGSIZE,p_prio);\
	if(-1 == ret)show_errno(0,"px_msgq_receive");\
	ret<1?-1:0;\
})

#define px_msgq_timedreceive(msg_ptr,mqdes,p_prio,tsv) ({\
	struct timespec ts={0};\
	int ret=clock_gettime(CLOCK_REALTIME, &ts);\
	if(-1 == ret)show_errno(0,"clock_gettime");\
	ts.tv_sec+=(tsv).tv_sec;\
	ts.tv_nsec+=(tsv).tv_nsec;\
	if(ts.tv_nsec>999999999){\
		ts.tv_sec+1;\
		ts.tv_nsec%=1000000000;\
	}\
	ret=mq_timedreceive(mqdes,msg_ptr,PX_MQ_MSGSIZE,p_prio,&ts);\
	if(-1 == ret)show_errno(0,"px_msgq_timedreceive");\
	ret?-1:0;\
})

#define px_msgq_notify(mqdes,p_sevp) ({\
	int ret=mq_notify(mqdes,p_sevp);\
	if(-1 == ret)show_errno(0,"px_msgq_notify");\
	ret?-1:0;\
})

extern mqd_t mqd;
#endif