#include <stdio.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <lzl/slog.h>
#include "my_socket.h"

int un_bind(int sfd,char *path){
	int ret=0;
	unlink(path);
	struct sockaddr_un addr={AF_UNIX};
	strncpy(addr.sun_path,path,sizeof(addr.sun_path));
	ret=my_bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret)return -1;
	return 0;
}
int un_connect(int sfd,char *path){
	int ret=0;
	struct sockaddr_un addr={AF_UNIX};
	strncpy(addr.sun_path,path,sizeof(addr.sun_path));
	ret=my_connect(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret)return -1;
	return 0;	
}
int in_bind(int sfd,short port,char *ip){
	int ret=0;
	struct sockaddr_in addr={AF_INET};	
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);
	ret=my_bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret)return -1;
	return 0;
}
int in_connect(int sfd,short port,char *ip){
	int ret=0;
	struct sockaddr_in addr={AF_INET};
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);
	ret=my_connect(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret)return -1;
	return 0;	
}