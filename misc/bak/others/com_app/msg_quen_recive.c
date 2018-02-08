#include "my_msg.h"
int main(void)
{
	int msgid; 
	msg_t data;
    long int msgtype = 0; //注意1  	
	if(-1==(msgid=msgget((key_t)1234, 0666 | IPC_CREAT))){
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  		
	}
	do{
		if(-1==msgrcv(msgid,&data,BUFSIZ,msgtype,0)){  
            fprintf(stderr, "msgsnd failed\n");  
            exit(EXIT_FAILURE);  
        } 
		printf("You wrote: %s\n",data.txt); 	
		sleep(1);
	}while(strncmp(data.txt, "end", 3));
	if(-1==msgctl(msgid,IPC_RMID,0))    {  
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);  
    }  
	exit(EXIT_SUCCESS); 		
}