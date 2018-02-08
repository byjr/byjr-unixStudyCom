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
pthread_t tid_ar[]={0}; 
typedef void *(*p_start_routine_t)(void *);
void *star_routine(void *args){
	int ret=0;
	int sock_fd=conn_fd;
	size_t ret_size=0;
	char buf[BUF_LENTH]="";
	war("%s:%d/%ld is done",__func__,getpid(),pthread_self());	
	do{
		char tmp[BUF_LENTH]="";
		memset(buf,0,sizeof(buf));
		ret_size=un_read(sock_fd,buf,sizeof(buf));
		strncpy(tmp,buf,sizeof(tmp));
		if(!ret_size){			
			war("%ld:%d exit!",pthread_self(),sock_fd);
			break;
		}
		inf(buf);		
		snprintf(buf,sizeof(buf)-ret_size,"%lu recived:%s!",pthread_self(),tmp);
		un_write(sock_fd,buf,sizeof(buf));
	}while(1);
}
void create_handle_thread(void){
	px_thread_create(&tid_ar[0],NULL,star_routine,NULL);
	px_thread_detach(tid_ar[0]);
	//px_thread_get_rtaddr(tid_ar[0]);	
}
int main (int argc, char *argv[])
{
	int ret=0;
	log_init(NULL);
	sock_fd=socket(AF_UNIX,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sock_fd){
		show_errno(0,"socket");
		exit(-1);
	}	
	unlink (UN_SOCK_PATH);
	struct sockaddr_un sock_addr={AF_UNIX,UN_SOCK_PATH};
	ret=bind(sock_fd,(struct sockaddr *)&sock_addr,sizeof(sock_addr));
	if(-1==ret){
		show_errno(0,"bind");
		exit(-1);
	}
	ret=listen(sock_fd,5);
	if(-1==ret){
		show_errno(0,"listen");
		exit(-1);
	}
	do{
		conn_fd=accept(sock_fd,NULL,0);
		if(-1==conn_fd){
			show_errno(0,"accept");
			exit(-1);
		}	
		create_handle_thread();		
	}while(1);
	return 0;
}