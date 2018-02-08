#include "my_msgq.c"
#include "my_sem.c"
#include <pthread.h>
#include <stdio.h>
int msgq = -1;
msg_st msg={0};
sem_t sem={0};
void *thread_start(void *arg) 
{
	while(1){
		int count=30;
		int val=0;
		my_sem_getvalue(&val,&sem);
		inf("my_sem_getvalue:%d",val);
		my_sem_wait(&sem);
		while(count--){
			if(!sv_msgqrcv_nowait(&msg,msgq,U2I_STOP)){
				war("rcv_no_wait:%s",msg.text);
				break;
			}	
			inf("proc.......................%d",count);
			usleep(100*1000);
		}		
		//sv_msgqsnd_nowait(msgq,"proc complet!",I2U_ANSW);		
	}
	
}
int main(int argc,char **argv)  
{  
	int ret=0;
	char buf[MSGQ_BUFF_SIZE]="";ipt("");
	pthread_t thread={0};ipt("");
	sv_msgqget(&msgq,U2I_MSG);ipt("");
	my_sem_init(&sem,0,0);ipt("");
	ret=pthread_create(&thread,NULL,thread_start,NULL);
	if(ret){
		err("pthread_create fail,errno:%d[%s].",errno,strerror(errno));
		return -1;
	}
	while(1){
		memset(msg.text,0,sizeof(msg.text));
		sv_msgqrcv(&msg,msgq,U2I_WORK);
		//inf("rcv:%s",msg.text);
		
		memset(msg.text,0,sizeof(msg.text));
		if(!sv_msgqrcv_nowait(&msg,msgq,U2I_STOP)){
			//inf("rcv_no_wait:%s",msg.text);
		}		
		my_sem_post(&sem,1);		
	}
	return 0;
} 
