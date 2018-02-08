#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <slog/slog.h>
int main(int argc,char *argv[])
{
	pid_t pid=0;
	pid=fork();
	switch(pid){
	case -1:
		err("");perror("fork");
		return -1;
	case 0: //The child process
		while(1){}
	default: //The parent process
		while(1){}
	}
}
