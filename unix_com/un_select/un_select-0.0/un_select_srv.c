#include "un_select.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
fd_set rfds={0};
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
	
	fd_set rfds={0};
	struct timeval tv={0};
	int retval={0};	
	FD_ZERO(&rfds);
    FD_SET(0, &rfds);
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