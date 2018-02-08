#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <lzl/my_socket.h>
#include <lzl/un_fop.h>
#include <sys/un.h>
#include <lzl/misc.h>
#include "my_epoll.h"
int epfd=0;
int ls_fd=-1;
struct sockaddr_un peeraddr={0};
socklen_t peerlen=sizeof(peeraddr);
char buf[BUF_SIZE]="";
struct epoll_event events[EVENTS_SIZE];
int main(int argc,char *argv[]){
	int ret=0,n_ready=0,i=0;
	log_init(NULL);
	ls_fd=my_socket(AF_UNIX,SOCK_STREAM,0);
	if(-1==ls_fd)return -1;
	ret=un_bind(ls_fd,UN_SOCKET_PATH);
	if(-1==ret)return -1;
	ret=my_listen(ls_fd,5);
	if(-1==ret)return -1;
	epfd=my_epoll_create(0);	
	if(epfd<0)return -1;
	add_ep_evt(epfd,ls_fd,EPOLLIN);	
	add_ep_evt(epfd,0,EPOLLIN);
	do{
		n_ready=my_epoll_wait(epfd,events,EVENTS_SIZE,-1,NULL);
		if(-1==n_ready){
			if(4==errno)continue;
			return -1;
		}
		for(i=0;i<n_ready;i++){
			int fd=events[i].data.fd;
			if(fd==ls_fd){
				if(n_ready+1<=EVENTS_SIZE){
					int conn=my_accept(ls_fd,&peeraddr,&peerlen);
					if(conn){
						add_ep_evt(epfd,conn,EPOLLIN);				
					}				
				}				
			}else if(EPOLLIN==events[i].events){
				memset(buf,0,sizeof(buf));
				size_t n=un_read(fd,buf,sizeof(buf));
				if(0==n){
					inf("peer close fd:%d",fd);
					del_ep_evt(epfd,fd,events[i].events);		
				}
				if(n>0){
					inf("s<-c:%s",buf);
					mod_ep_evt(epfd,fd,EPOLLOUT);
				}
			}else if(EPOLLOUT==events[i].events){
				strncat(buf,":s->c",sizeof(buf)-strlen(buf)-1);
				size_t n=un_write(fd,buf,strlen(buf));
				if(n>0){
					mod_ep_evt(epfd,fd,EPOLLIN);
				}			
			}
		}
	}while(1);
	return 0;
}