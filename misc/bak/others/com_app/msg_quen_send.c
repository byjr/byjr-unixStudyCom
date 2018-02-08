#include "my_msg.h"
int main()
{
	int msgid; 
	msg_t data;
	if(-1==(msgid=msgget((key_t)1234, 0666 | IPC_CREAT))){
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  		
	}
	do{
		printf("Enter some text under num %d: ",BUFSIZ); 
		data.type=1;
		fgets(data.txt,BUFSIZ,stdin); 		
		if(-1==msgsnd(msgid,&data,BUFSIZ,0)){  
            fprintf(stderr, "msgsnd failed\n");  
            exit(EXIT_FAILURE);  
        } 
		sleep(1);
	}while(strncmp(data.txt, "end", 3));
	exit(EXIT_SUCCESS); 
}