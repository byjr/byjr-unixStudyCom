#include "my_socket.h"

int un_bind(int sfd,char *path){
	unlink(path);
	struct sockaddr_un addr={AF_UNIX};
	strncpy(addr.sun_path,path,sizeof(addr.sun_path));
	int ret=my_bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret)return -1;
	return 0;
}
int un_connect(int sfd,char *path){
	struct sockaddr_un addr={AF_UNIX};
	strncpy(addr.sun_path,path,sizeof(addr.sun_path));
	int ret=my_connect(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret)return -1;
	return 0;
}
int in_bind(int sfd,char *ip,in_port_t port){
	struct sockaddr_in addr={AF_INET};
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);
	int ret=my_bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret)return -1;
	return 0;
}
int in_connect(int sfd,char *ip,in_port_t port){
	struct sockaddr_in addr={AF_INET};
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);
	int ret=my_connect(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret)return -1;
	return 0;
}
int un_tcp_cli_create(char *path){
	int sfd=my_socket(AF_UNIX,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sfd)return -1;
	int ret=un_connect(sfd,path);
	if(-1==ret)return -2;
	return sfd;
}
int in_tcp_cli_create(char *ip,in_port_t port){
	int sfd=my_socket(AF_INET,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sfd)return -1;
	int ret=in_connect(sfd,ip,port);
	if(-1==ret)return -2;
	return sfd;
}
int in_udp_cli_create(char *ip,in_port_t port){
	int sfd=my_socket(AF_INET,SOCK_DGRAM,0);
	if(-1==sfd)return -1;
	int ret=in_connect(sfd,ip,port);
	if(-1==ret)return -2;
	return sfd;
}
int un_udp_cli_create(char *addr){
	int sfd=my_socket(AF_UNIX,SOCK_DGRAM,0);
	if(-1==sfd)return -1;
	if(NULL==addr) return sfd;
	int ret=un_bind(sfd,addr);
	if(-1==ret)return -2;
	return sfd;
}
void in_epoll_tcp_server(net_serv_t *pServ){
	int sfd=my_socket(AF_INET,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sfd)exit(-1);
	pServ->fd=sfd;
	int ret=1;
	ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,
		&ret,sizeof(ret));
	if(-1==ret)exit(-1);
	ret=in_bind(sfd,pServ->addr,pServ->port);
	if(-1==ret)exit(-1);
	ret=my_listen(sfd,SOMAXCONN);
	if(-1==ret)exit(-1);
	int epfd=my_epoll_create(0);
	if(epfd<0)exit(-1);
	add_ep_evt(epfd,sfd,EPOLLIN,NULL);
	struct epoll_event events[EVENTS_SIZE]={0};
	do{
		int nReady=my_epoll_wait(epfd,events,EVENTS_SIZE,-1,NULL);
		if(-1==nReady){
			if(4==errno)continue;
			exit(-1);
		}
		if(0==nReady)continue;
		struct sockaddr_in peerAddr={AF_INET};
		socklen_t peerLen=sizeof(peerAddr);
		int i=0;
		for(i=0;i<nReady;i++){
			int fd=events[i].data.fd;
			if(fd==sfd){
				if(nReady+1<=EVENTS_SIZE){
					int conn=my_accept(sfd,&peerAddr,&peerLen);
					if(0==conn)continue;
					add_ep_evt(epfd,conn,EPOLLIN,NULL);
				}
			}else if(EPOLLIN==events[i].events){
				ret=pServ->pRcbk(fd);
				if(0==ret){
					mod_ep_evt(epfd,fd,EPOLLOUT,NULL);
				}else if(1==ret){
					del_ep_evt(epfd,fd,EPOLLIN,NULL);
					inf("peer close fd:%d",fd);
				}
			}else if(EPOLLOUT==events[i].events){
				ret=pServ->pWcbk(fd);
				if(0==ret){
					mod_ep_evt(epfd,fd,EPOLLIN,NULL);
				}else if(1==ret){
					del_ep_evt(epfd,fd,EPOLLOUT,NULL);
					inf("peer close fd:%d",fd);
				}
			}
		}
	}while(1);
}
void in_epoll_udp_server(net_serv_t tbl[],size_t count){
	int epfd=my_epoll_create(0);
	if(epfd<0)exit(-1);
	size_t i=0,ret=0;
	for(i=0;i<count;i++){
		tbl[i].fd=my_socket(AF_INET,SOCK_DGRAM,0);
		if(-1==tbl[i].fd)exit(-1);
		int ret=setsockopt(tbl[i].fd,SOL_SOCKET,SO_REUSEADDR,
			&ret,sizeof(ret));
		if(ret<0)exit(-1);
		ret=in_bind(tbl[i].fd,tbl[i].addr,tbl[i].port);
		if(-1==ret)exit(-1);
		add_ep_evt(epfd,tbl[i].fd,EPOLLIN,&tbl[i]);
	}
	struct epoll_event events[EVENTS_SIZE]={0};
	do{
		int nReady=my_epoll_wait(epfd,events,EVENTS_SIZE,-1,NULL);
		if(-1==nReady){
			if(4==errno)continue;
			exit(-1);
		}
		if(0==nReady)continue;
		struct sockaddr_in peerAddr={AF_INET};
		socklen_t peerLen=sizeof(peerAddr);
		int i=0;
		for(i=0;i<nReady;i++){
			net_serv_t* pServ=(net_serv_t*)events[i].data.ptr;
			int fd=pServ->fd;
			if(EPOLLIN==events[i].events){
				ret=pServ->pRcbk(fd);
				if(0==ret){
					mod_ep_evt(epfd,fd,EPOLLOUT,pServ);
				}else if(1==ret){
					del_ep_evt(epfd,fd,EPOLLIN,pServ);
					inf("peer close fd:%d",fd);
				}
			}else if(EPOLLOUT==events[i].events){
				ret=pServ->pWcbk(fd);
				if(0==ret){
					mod_ep_evt(epfd,fd,EPOLLIN,pServ);
				}else if(1==ret){
					del_ep_evt(epfd,fd,EPOLLOUT,pServ);
					inf("peer close fd:%d",fd);
				}
			}
		}
	}while(1);
}

void un_epoll_udp_server(net_serv_t tbl[],size_t count){
	int epfd=my_epoll_create(0);
	if(epfd<0)exit(-1);
	size_t i=0,ret=0;
	for(i=0;i<count;i++){
		tbl[i].fd=my_socket(AF_UNIX,SOCK_DGRAM,0);
		if(-1==tbl[i].fd)exit(-1);
		unlink(tbl[i].addr);
		ret=un_bind(tbl[i].fd,tbl[i].addr);
		if(-1==ret)exit(-1);
		add_ep_evt(epfd,tbl[i].fd,EPOLLIN,&tbl[i]);
	}
	struct epoll_event events[EVENTS_SIZE]={0};
	do{
		int nReady=my_epoll_wait(epfd,events,EVENTS_SIZE,-1,NULL);
		if(-1==nReady){
			if(4==errno)continue;
			exit(-1);
		}
		if(0==nReady)continue;
		struct sockaddr_un peerAddr={AF_UNIX};
		socklen_t peerLen=sizeof(peerAddr);
		int i=0;
		for(i=0;i<nReady;i++){
			net_serv_t* pServ=(net_serv_t*)events[i].data.ptr;
			int fd=pServ->fd;
			if(EPOLLIN==events[i].events){
				ret=pServ->pRcbk(fd);
				if(0==ret){
					mod_ep_evt(epfd,fd,EPOLLOUT,pServ);
				}else if(1==ret){
					del_ep_evt(epfd,fd,EPOLLIN,pServ);
					inf("peer close fd:%d",fd);
				}
			}else if(EPOLLOUT==events[i].events){
				ret=pServ->pWcbk(fd);
				if(0==ret){
					mod_ep_evt(epfd,fd,EPOLLIN,pServ);
				}else if(1==ret){
					del_ep_evt(epfd,fd,EPOLLOUT,pServ);
					inf("peer close fd:%d",fd);
				}
			}
		}
	}while(1);
}

void un_epoll_tcp_server(net_serv_t *pServ){
	int sfd=my_socket(AF_UNIX,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sfd)exit(-1);
	pServ->fd=sfd;
	unlink(pServ->addr);
	int ret=un_bind(sfd,pServ->addr);
	if(-1==ret)exit(-1);
	ret=my_listen(sfd,SOMAXCONN);
	if(-1==ret)exit(-1);
	int epfd=my_epoll_create(0);
	if(epfd<0)exit(-1);
	add_ep_evt(epfd,sfd,EPOLLIN,NULL);
	struct epoll_event events[EVENTS_SIZE]={0};
	do{
		int nReady=my_epoll_wait(epfd,events,EVENTS_SIZE,-1,NULL);
		if(-1==nReady){
			if(4==errno)continue;
			exit(-1);
		}
		if(0==nReady)continue;
		struct sockaddr_un peerAddr={AF_UNIX};
		socklen_t peerLen=sizeof(peerAddr);
		int i=0;
		for(i=0;i<nReady;i++){
			int fd=events[i].data.fd;
			if(fd==sfd){
				if(nReady+1<=EVENTS_SIZE){
					int conn=my_accept(sfd,&peerAddr,&peerLen);
					if(0==conn)continue;
					add_ep_evt(epfd,conn,EPOLLIN,NULL);
				}
			}else if(EPOLLIN==events[i].events){
				ret=pServ->pRcbk(fd);
				if(0==ret){
					mod_ep_evt(epfd,fd,EPOLLOUT,NULL);
				}else if(1==ret){
					del_ep_evt(epfd,fd,EPOLLIN,NULL);
					inf("peer close fd:%d",fd);
				}
			}else if(EPOLLOUT==events[i].events){
				ret=pServ->pWcbk(fd);
				if(0==ret){
					mod_ep_evt(epfd,fd,EPOLLIN,NULL);
				}else if(1==ret){
					del_ep_evt(epfd,fd,EPOLLOUT,NULL);
					inf("peer close fd:%d",fd);
				}
			}
		}
	}while(1);
}
