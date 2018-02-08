#include "my_socket.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <signal.h>
#include <lzl/px_thread.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/un_fop.h>
int sock_fd=0;
int conn_fd=0;
int count=0;
int len=0;
char buf[BUF_LENTH]="";
void signal_handle(int signo){
	int ret=0;
	switch(signo){	
	case 34:{
		memset(buf,0,sizeof(buf));
		len=sprintf(buf,"send:%d",count++);
		un_write(sock_fd,buf,MIN(BUF_LENTH,len,size_t));	
		memset(buf,0,BUF_LENTH);
		un_read(sock_fd,buf,BUF_LENTH);
		raw("%s\n",buf);		
		break;
	}	
	default:
		inf("recive signal:%d!",signo);
		break;
	}
}
int main (int argc, char *argv[])
{
	int ret=0,i=0;
	log_init(NULL);
	for(i=SIGRTMIN;i<=SIGRTMAX;i++){
		signal(i,signal_handle);		
	}		
	sock_fd=my_socket(AF_UNIX,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sock_fd)exit(-1);
	struct sockaddr_un sock_addr={AF_UNIX,UN_SOCK_PATH};	
	ret=my_connect(sock_fd,(struct sockaddr *)&sock_addr,sizeof(sock_addr));
	if(-1==ret)exit(-1);
	do{
		memset(buf,0,BUF_LENTH);
		raw("plaese input some info:\n")
		scanf("%1024s",buf);
		len=strlen(buf);
		un_write(sock_fd,buf,MIN(BUF_LENTH,len,size_t));
		memset(buf,0,BUF_LENTH);
		un_read(sock_fd,buf,BUF_LENTH);
		raw("%s\n",buf);
	}while(1);
	return 0;
}