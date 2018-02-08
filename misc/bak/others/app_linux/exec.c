#include <unistd.h>
#include "stdio.h"
#include<stdlib.h>
#define log printf
#define CURRENT_FUNC 2
char *argv[4]={
	"lz",
	"3",
	"xxxx",
	NULL
};
char *argv1[4]={
	"lz",
	"3",
	"----",
	NULL
};
int main(void){
#if CURRENT_FUNC == 0
	if(execl("./lz","lz","10",NULL)==-1){
		perror("execl error");
		exit(-1);
	}	
	log("execl error.\r\n");
#elif 	CURRENT_FUNC == 1
	if(execv("./lz",argv)==-1){
		perror("execl error");
		exit(-1);
	}	
#elif 	CURRENT_FUNC == 2
	pid_t pid=fork();
	if(pid==-1){
		perror("fork error:");
		exit(-1);
	}
	if(pid==0){
		printf("The child pid is %d\n",getpid());
		if(execv("./lz",argv)==-1){
			perror("execl error");
			exit(-1);
		}			
	}
	pid=fork();
	if(pid==-1){
		perror("fork error:");
		exit(-1);
	}
	if(pid==0){
		printf("The child pid is %d\n",getpid());
		if(execv("./lz",argv1)==-1){
			perror("execl error");
			exit(-1);
		}			
	}
#endif
	return 0;
}