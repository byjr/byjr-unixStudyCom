
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <signal.h>
#include <lzl/px_thread.h>
#include <lzl/misc.h>
#include <lzl/un_fop.h>
#include <lzl/my_socket.h>
#include "my_epoll.h"
int sock_fd=0;
int conn_fd=0;
int count=0;
int len=0;
char buf[BUF_SIZE]="";
int main (int argc, char *argv[]){
	int ret=0;
	log_init("l=11111");
	sock_fd=my_socket(AF_UNIX,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sock_fd)exit(-1);
	ret=un_connect(sock_fd,UN_SOCKET_PATH);
	if(-1==ret)exit(-1);
	do{
		memset(buf,0,BUF_SIZE);
		raw("plaese input some info:\n")
		scanf("%1024s",buf);
		len=strlen(buf);
		un_write(sock_fd,buf,MIN(BUF_SIZE,len,size_t));
		memset(buf,0,BUF_SIZE);
		un_read(sock_fd,buf,BUF_SIZE);
		raw("%s\n",buf);
	}while(1);
	return 0;
}