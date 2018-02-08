#include "my_msgq.c"
#include <stdio.h>
#include <string.h>
int msgq = -1; 
msg_st msg={0};

int main(int argc,char **argv)  
{
	char buf[MSGQ_BUFF_SIZE]="";	
	sv_msgqget(&msgq,U2I_MSG);
	while(1){
		fgets(buf,MSGQ_BUFF_SIZE,stdin);
		
		sv_msgqsnd_nowait(msgq,"stop proc!",U2I_STOP);
		sleep(1);
		//if(!sv_msgqrcv_nowait(&msg,msgq,I2U_ANSW))
		{
			sv_msgqsnd_nowait(msgq,buf,U2I_WORK);
			//inf("iflytek answer:%s",msg.text);
		}
	}
	return 0;
} 
