#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <signal.h>
#include <lzl/px_thread.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/un_fop.h>
#include "my_socket.c"
#define BUF_LENTH MSG_BUF_BYTE
char buf[BUF_LENTH]="";
int main (int argc, char *argv[]){
	log_init("l=11111");
	// int sfd=un_tcp_cli_create(UN_SOCK_PATH);
	int sfd=in_tcp_cli_create(SERVER_IP,PORT_NUM);
	if(sfd<0)return -1;
	do{
		bzero(buf,sizeof(buf));
		raw("plaese input some info:\n")
		scanf("%1024s",buf);
		size_t len=strlen(buf);
		inf(buf);
		un_write(sfd,buf,MIN(BUF_LENTH,len,size_t));
		inf(buf);
		bzero(buf,BUF_LENTH);
		un_read(sfd,buf,BUF_LENTH);
		raw("%s\n",buf);
	}while(1);
}