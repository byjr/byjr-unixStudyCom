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
	// int sfd=un_tcp_cli_create(SRV_ADDR);
	// int sfd=in_tcp_cli_create(SERVER_IP,PORT_NUM);
	int sfd=in_udp_cli_create(SERVER_IP,PORT_NUM);
	// int sfd=un_udp_cli_create(CLI_ADDR,NULL);
	if(sfd<0)return -1;
	// struct sockaddr_un addr={AF_UNIX,SRV_ADDR};
	struct sockaddr_in addr={AF_INET,0,PORT_NUM};
	socklen_t addr_len=sizeof(addr);
	do{
		bzero(buf,sizeof(buf));
		if(argv[1]){
			snprintf(buf,sizeof(buf),">>%s<<",argv[1]);
		}else{
			raw("plaese input some info:\n");
			scanf("%1024s",buf);
		}
		size_t len=strlen(buf);
		// my_sendto(sfd,buf,strlen(buf),0,&addr,addr_len);
		un_write(sfd,buf,MIN(BUF_LENTH,len,size_t));
		bzero(buf,BUF_LENTH);
		// my_recvfrom(sfd,buf,sizeof(buf),0,&addr,&addr_len);
		un_read (sfd,buf,BUF_LENTH);
		raw("%s\n",buf);
	}while(1);
}