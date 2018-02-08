#include "my_shm.h"
int main(){
	struct shared_use_st *shared = NULL; 	
	int shmid;  
	if(-1==shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT)){
		fprintf(stderr, "shmget failed\n");  
        exit(EXIT_FAILURE);  
	}
	if(-1==shared=(struct shared_use_st *)shmat(shmid,(void *)0,0)){
        fprintf(stderr, "shmat failed\n");  
        exit(EXIT_FAILURE);  		
	}
	printf("Memory attached at %p\n", shm); 
	shared->written = 0;
	do{
		while(shared->written != 1){  
            sleep(1);  
            printf("Waiting...\n");  
        } 
		printf("read some text: "); 
		printf("%s\r\n",shared.text);
		shared->written = 0; 		
	}while(strncmp(shared.text, "end", 3));
	if(-1==shmdt(shmid)){
        fprintf(stderr, "shmdt failed\n");  
        exit(EXIT_FAILURE);  		
	}
    sleep(2); 
    exit(EXIT_SUCCESS); 	
}
