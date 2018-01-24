#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include "misc.h"
#include "slog.h"
#include "px_msgq.h"

int px_msgq_set_attr(mqd_t mqdes, const struct mq_attr *p_new,struct mq_attr *p_old)
{//设置为非阻塞仅对本进程有效
	int ret=0;
	if(!p_new){
		err("p_new is NULL");
		return -1;
	}
	ret=mq_setattr(mqdes,p_new,p_old);
	if(-1 == ret){
		show_error(ret,__func__);
		return -1;
	}
	return 0;
}
int px_msgq_getattr(struct mq_attr *p_attr,mqd_t mqdes)
{
	int ret=0;
	ret=mq_getattr(mqdes,p_attr);
	if(-1 == ret){
		show_error(ret,__func__);
		return -1;
	}
	return 0;
}
int px_msgq_showattr(struct mq_attr *p_attr)
{
	if(NULL==p_attr){
		err("p_attr is NULL");
		return -1;
	}
	inf("mq_flags	=%ld",p_attr->mq_flags	);   
	inf("mq_maxmsg	=%ld",p_attr->mq_maxmsg	);  
	inf("mq_msgsize	=%ld",p_attr->mq_msgsize); 
	inf("mq_curmsgs	=%ld",p_attr->mq_curmsgs); 
	return 0;
}
int px_msgq_open(mqd_t *p_mqd,const char *name)
{
	mqd_t mqd={0};
	struct mq_attr init_attr={
		.mq_maxmsg	=PX_MQ_MAXMSG_COUNT,
		.mq_msgsize	=PX_MQ_MSGSIZE,
	};	
	mqd=mq_open(name,O_CREAT|O_RDWR,S_IRUSR|S_IWUSR,&init_attr);
	if((mqd_t) -1 == mqd){
		show_error((mqd_t)mqd,__func__);
		exit(-1);
	}
	*p_mqd=mqd;
	return 0;
}
int px_msgq_send(mqd_t mqdes, const char *msg_ptr, unsigned int msg_prio)
{
	int ret=0;
	ret=mq_send(mqdes,msg_ptr,PX_MQ_MSGSIZE,msg_prio);
	if(-1 == ret){
		show_error(ret,__func__);
		return -1;		
	}
	return 0;
}
int px_msgq_timedsend(mqd_t mqdes, const char *msg_ptr, unsigned int msg_prio,int sec)
{
	int ret=0;
	struct timespec ts={0};
	ret=clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec+=sec;
	if(-1 == ret){
		show_error(ret,"clock_gettime");
	}	
	ret=mq_timedsend(mqdes,msg_ptr,PX_MQ_MSGSIZE,msg_prio,&ts);
	if(-1 == ret){
		show_error(ret,__func__);
		return -1;		
	}
	return 0;
}
int px_msgq_receive(char *msg_ptr, mqd_t mqdes,unsigned int *msg_prio)
{
	int ret=0;	
	ret=mq_receive(mqdes,msg_ptr,PX_MQ_MSGSIZE,msg_prio);
	if(-1 == ret){
		show_error(ret,__func__);
		exit(-1);
	}
	return 0;
}
int px_msgq_timedreceive(char *msg_ptr,mqd_t mqdes,unsigned int *msg_prio,int sec)
{
	int ret=0;
	struct timespec ts={0};
	ret=clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec+=sec;
	if(-1 == ret){
		show_error(ret,"clock_gettime");
	}	
	ret=mq_timedreceive(mqdes,msg_ptr,PX_MQ_MSGSIZE,msg_prio,&ts);
	if(-1 == ret){
		show_error(ret,__func__);
		return -1;
	}
	return 0;
}
int px_msgq_notify(mqd_t mqdes, const struct sigevent *p_sevp)
{
	int ret=0;
	ret=mq_notify(mqdes,p_sevp);
	if(-1 == ret){
		show_error(ret,__func__);
		return -1;
	}
	return 0;
}	



