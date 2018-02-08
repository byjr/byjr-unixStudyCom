#include "my_socket.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <lzl/px_thread.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/un_fop.h>
int sock_fd=0;
int conn_fd=0;
int main (int argc, char *argv[])
{
	int ret=0,len=0;
	log_init(NULL);
	char buf[BUF_LENTH]="";
	sock_fd=socket(AF_UNIX,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sock_fd){
		show_errno(0,"socket");
		exit(-1);
	}	
	struct sockaddr_un sock_addr={AF_UNIX,UN_SOCK_PATH};	
	ret=connect(sock_fd,(struct sockaddr *)&sock_addr,sizeof(sock_addr));
	if(-1==ret){
		show_errno(0,"connect");
		exit(-1);		
	}
	do{
		memset(buf,0,BUF_LENTH);
		inf("plaese input some info:")
		scanf("%1024s\n",buf);
		len=strlen(buf);
		un_write(sock_fd,buf,MIN(BUF_LENTH,len,size_t));
		memset(buf,0,BUF_LENTH);
		un_read(sock_fd,buf,BUF_LENTH);
		raw("%s\n",buf);
	}while(1);
	return 0;
}