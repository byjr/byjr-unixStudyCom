#ifndef PX_MSGQ_H
#define PX_MSGQ_H 1
		   
int mq_unlink(const char *name);//删除链接数
int mq_close(mqd_t mqdes);

#ifndef PX_MQ_MAXMSG_COUNT
#define PX_MQ_MAXMSG_COUNT 8
#endif

#ifndef PX_MQ_MSGSIZE
#define PX_MQ_MSGSIZE 100
#endif 

#endif