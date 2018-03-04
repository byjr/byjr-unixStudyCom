#include "px_msgq.c"
#include <signal.h>
#define MSG_PRIO 5
unsigned int msg_prio=MSG_PRIO;
int start_handle(void *args){
	inf(__func__);
	return 0;
}
int send_handle(void *args){
	char **argv=(char **)args;
	IS_ARG_COUNT_LESS_THAN(2);
	int ret=px_msgq_send(mqd,argv[1],argv[2][0]-'0');
	if(ret<0) return -1;	
	return 0;
}
int aset_handle(void *args){
	struct mq_attr attr={0};
	int ret=px_msgq_getattr(&attr,mqd);
	if(ret<0) return -1;
	attr.mq_flags=O_NONBLOCK;
	ret=px_msgq_setattr(mqd,&attr);
	if(ret<0) return -1;
	px_msgq_showattr(&attr);
	return 0;
}
int tdsnd_handle(void *args){
	struct timespec tsv={1,500000000};
	char **argv=(char **)args;	
	// IS_ARG_COUNT_LESS_THAN(2);
	int ret=px_msgq_timedsend(mqd,argv[1],5,tsv);
	if(ret<0) return -1;	
	return 0;
}
int tdrcv_handle(void *args){
	struct timespec tsv={1,0};
	char **argv=(char **)args;	
	// IS_ARG_COUNT_LESS_THAN(2);
	int ret=px_msgq_timedreceive(argv[1],mqd,&msg_prio,tsv);
	if(ret<0) return -1;	
	return 0;
}
struct sigevent sev={0};
static void tfunc(union sigval sv){
	int ret=px_msgq_notify(mqd,&sev);
	if(ret<0)return;
	char msg_buf[PX_MQ_MSGSIZE]="";
	ret=px_msgq_receive(msg_buf,mqd,&msg_prio);
	if(ret<0)return;	
	err("msg_buf:%s",msg_buf);
	sleep(1);
}
int ntf_handle(void *args){	
	char **argv=(char **)args;
	signal(SIGUSR1,(void (*)(int))tfunc);
	inf(argv[1]);
	if(!strcmp(argv[1],"thread")){inf("");
		sev.sigev_notify = SIGEV_THREAD;
        sev.sigev_notify_function = tfunc;
        // sev.sigev_notify_attributes = NULL;
        // sev.sigev_value.sival_ptr = &t_mq;   /* Arg. to thread func. */
	}else if(!strcmp(argv[1],"signal")){inf("");
		sev.sigev_notify = SIGEV_SIGNAL;
        sev.sigev_signo	 = SIGUSR1;	
	}
	int ret=px_msgq_notify(mqd,&sev);inf("ret=%d",ret);
	if(ret<0){
		return -1;
	}
	do{
		// inf("px_msg:%s",px_msg);
		sleep(1);
	}while(1);		
	return 0;
}
fifo_cmd_t fifo_cmd_tbl[]={
	ADD_CMD_ITEM(start)
	ADD_CMD_ITEM(send)
	ADD_CMD_ITEM(aset)
	ADD_CMD_ITEM(tdsnd)
	ADD_CMD_ITEM(tdrcv)
	ADD_CMD_ITEM(ntf)	
};
int tools_init(void *args){
	mqd=px_msgq_open("/mq0");
	if(mqd<0) return -1;
	return 0;
}
int main(int argc,char *argv[]){
	log_init("l=11111");
	
	int ret=fifo_cmd_init();
	if(ret<0)return -1;

	ret=tools_init(NULL);
	if(ret<0) return -1;	
	
	pid_t pid=fork();
	switch(pid){
	case 0:{//子进程
			inf("my_pid is:%d",getpid());
			char *argv1[2]={"ntf","signal"};
			ntf_handle(argv1);
			do{
				char msg_buf[PX_MQ_MSGSIZE]="";
				int ret=px_msgq_receive(msg_buf,mqd,&msg_prio);
				if(ret<0) continue;
				inf(msg_buf);
			}while(1);
		}
		break;
	case -1:
			err("fork failure!");
		break;
	default:
		break;
	}
	inf("my_pid is:%d",getpid());
	do{
		fifo_cmd_wait();
		fifo_cmd_proc(fifo_cmd_tbl,getCount(fifo_cmd_tbl));
	}while(1);
}