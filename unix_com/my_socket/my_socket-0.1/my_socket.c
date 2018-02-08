#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <slog/slog.h>
#include "my_socket.h"
#include <sys/types.h>
#include <sys/socket.h>

int create_my_socket(int *p_fd)
{
	int sfd=0;
	sfd=socket(AF_UNIX,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sfd){
		err("");perror("socket");
		return -1;
	}
	*p_fd=sfd;
	return 0;
}
int bind_my_socket(int fd,char *path)
{
	int ret=0;
	struct sockaddr_un addr={0};
	unlink (path);
	addr.sun_family=AF_UNIX;
	strncpy (addr.sun_path,path,sizeof(addr.sun_path)-1);
	ret=bind(fd,(struct sockaddr *)&addr,sizeof(addr));
	if(-1==ret){
		err("");perror("bind");
		return -1;
	}
	return 0;
}
int listen_socket(int fd,int maximum)
{
	int ret=0;
	ret=listen(fd,maximum);
	if(-1==ret){
		err("");perror("listen");
		return -1;
	}
	return 0;
}
int accept_client(int *p_cfd,int sfd)
{
	int ret=0,cfd=0;
	cfd=accept4(sfd,NULL,NULL,SOCK_CLOEXEC);
	if(-1==cfd){
		err("");perror("accept");
		return -1;
	}
	*p_cfd=cfd;
	return 0;	
}
int accept_client_no_wait(int *p_cfd,int sfd)
{
	int ret=0,cfd=0;
	cfd=accept4(sfd,NULL,NULL,SOCK_NONBLOCK|SOCK_CLOEXEC);
	if(-1==cfd){
		err("");perror("accept");
		return -1;
	}
	*p_cfd=cfd;
	return 0;	
}
int connect_un_server(int fd,char *path)
{
	int ret=0;
	struct sockaddr_un addr={0};
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,path,sizeof(addr.sun_path)-1);
	ret=connect(fd,&addr,sizeof(addr));
	if(-1==ret){
		err("");perror("connect");
		return -1;
	}
	return 0;	
}