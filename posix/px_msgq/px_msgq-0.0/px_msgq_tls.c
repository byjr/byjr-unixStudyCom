#include "px_msgq.c"
#include <signal.h>
#include <unistd.h>

#define TTT_PX_MSGQ "/ttt1"

#define IS_ARG_COUNT_LESS_THAN(x) \
	if(NULL==argv[x]){\
		err("too few args!");\
		return -1;\
	}
	
typedef struct misc_cmd_t{
	char *cmd;
	int (*handle)(void *);
}misc_cmd_t;

mqd_t t_mq={0};
char px_msg[PX_MQ_MSGSIZE]="";

int snd_handle(void *args)
{
	char **argv=(char **)args;	
	IS_ARG_COUNT_LESS_THAN(2);
	bzero(px_msg,sizeof(px_msg));	
	strncpy(px_msg,argv[2],sizeof(px_msg)-1);
	int ret=0;
	if(argv[3]){
		if(!strcmp(argv[3],"nb")){
			struct mq_attr attr,old_mq_attr,new_mq_attr={
				.mq_flags=O_NONBLOCK,
			};
			px_msgq_set_attr(t_mq,&new_mq_attr,&old_mq_attr);
			px_msgq_getattr(&attr,t_mq);
			px_msgq_showattr(&old_mq_attr);
			inf("----------------------------------------");
			px_msgq_showattr(&attr);
		}
		int sec=0;
		ret=sscanf(argv[3],"t=%d",&sec);
		if(ret){
			ret=px_msgq_timedsend(t_mq,px_msg,0,sec);
			goto Exit0;
		}
	}	
	ret=px_msgq_send(t_mq,px_msg,0);
Exit0:	
	if(ret<0){
		return -1;
	}
	return 0;
}
int rcv_handle(void *args)
{
	char **argv=(char **)args;	
	int ret=0;		
	bzero(px_msg,sizeof(px_msg));
	int sec=0;
	if(argv[2]){
		if(!strcmp(argv[2],"nb")){
			struct mq_attr attr,new_mq_attr={
				.mq_flags=O_NONBLOCK,
			};
			px_msgq_set_attr(t_mq,&new_mq_attr,NULL);
			px_msgq_getattr(&attr,t_mq);
			inf("----------------------------------------");
			px_msgq_showattr(&attr);
		}		
		ret=sscanf(argv[2],"t=%d",&sec);
		if(ret){
			ret=px_msgq_timedreceive(px_msg,t_mq,0,sec);
			goto Exit0;
		}
	}
	ret=px_msgq_receive(px_msg,t_mq,0);
Exit0:	
	if(ret<0){
		return -1;
	}
	inf("px_msg:%s",px_msg);
	return 0;
}
int set_handle(void *args)
{
	char **argv=(char **)args;	
	int ret=0;
	struct mq_attr new_mq_attr={
		.mq_flags=O_NONBLOCK,
	};
	ret=px_msgq_set_attr(t_mq,&new_mq_attr,NULL);
	if(ret<0){
		return -1;
	}
	do{	
		bzero(&new_mq_attr,sizeof(new_mq_attr));
		px_msgq_getattr(&new_mq_attr,t_mq);	
		inf("----------------------------------------");
		px_msgq_showattr(&new_mq_attr);
		sleep(1);
	}while(0);
	return 0;
}
struct sigevent sev={0};
static void tfunc(union sigval sv)
{
	px_msgq_notify(t_mq,&sev);
	bzero(px_msg,sizeof(px_msg));
	px_msgq_receive(px_msg,t_mq,0);
	inf("px_msg:%s",px_msg);
	sleep(1);
}
int ntf_handle(void *args)
{	
	char **argv=(char **)args;
	IS_ARG_COUNT_LESS_THAN(2);
	mq_unlink(TTT_PX_MSGQ);
	px_msgq_open(&t_mq,TTT_PX_MSGQ);
	signal(SIGUSR1,(void (*)(int))tfunc);
	int ret=0;
	if(!strcmp(argv[2],"thread")){
		sev.sigev_notify = SIGEV_THREAD;
        sev.sigev_notify_function = tfunc;
        // sev.sigev_notify_attributes = NULL;
        // sev.sigev_value.sival_ptr = &t_mq;   /* Arg. to thread func. */
	}else if(!strcmp(argv[2],"signal")){
		sev.sigev_notify = SIGEV_SIGNAL;
        sev.sigev_signo	 = SIGUSR1;	
	}
	ret=px_msgq_notify(t_mq,&sev);
	if(ret<0){
		return -1;
	}
	do{
		// inf("px_msg:%s",px_msg);
		sleep(1);
	}while(1);		
	return 0;
}

misc_cmd_t misc_cmd_tbl[]={
	{"snd",		snd_handle					},
	{"rcv",		rcv_handle					},
	{"set",		set_handle					},
	{"ntf",		ntf_handle					},
};
int main(int argc,char **argv)
{
	IS_ARG_COUNT_LESS_THAN(1);
	px_msgq_open(&t_mq,TTT_PX_MSGQ);
	int i=0;
	int cmd_count=sizeof(misc_cmd_tbl)/sizeof(misc_cmd_tbl[0]);
	for(i=0;i<cmd_count;i++){
		if(!strcmp(argv[1],misc_cmd_tbl[i].cmd)){
			int ret=0;
			ret=misc_cmd_tbl[i].handle(argv);
			if(ret<0){
				return -2;
			}
			return 0;
		}
	}
	return -3;
}



