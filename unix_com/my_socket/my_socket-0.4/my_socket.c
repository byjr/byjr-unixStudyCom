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
int in_bind(int sfd,char *ip,in_port_t port){
	int ret=0;
	struct sockaddr_in addr={AF_INET};	
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);
	ret=my_bind(sfd,(struct sockaddr*)&addr,sizeof(addr));
	if(ret)return -1;
	return 0;
}
int in_connect(int sfd,char *ip,in_port_t port){
	int ret=0;
	struct sockaddr_in addr={AF_INET};
	addr.sin_port=htons(port);
	addr.sin_addr.s_addr=inet_addr(ip);
	ret=my_connect(sfd,(struct sockaddr*)&addr,sizeof(addr));
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
void un_my_select_tcp_server(char *path,proc_t proc){
	size_t i=0;
	#define BUF_SIZE MSG_BUF_BYTE
	char buf[BUF_SIZE]="";
	int conn_a[FD_SETSIZE]={0};
	for(i=0;i<getCount(conn_a);i++)conn_a[i]=-1;
	int sfd=my_socket(AF_UNIX,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sfd)exit(-1);
	unlink(path);
	int ret=0;
	ret=un_bind(sfd,path);
	if(-1==ret)exit(-1);
	ret=my_listen(sfd,SOMAXCONN);
	if(-1==ret)exit(-1);
	int maxfd=sfd;
	fd_set rset={0},allset={0};
	FD_SET(maxfd,&allset);
	do{
		rset=allset;
		int nready=my_select(maxfd+1,&rset,NULL,NULL,NULL,NULL);
		if(nready<0){
			if(EINTR==errno)continue;//防止收到信号时退出
			show_errno(0,"my_select");
			exit(-1);
		}
		if(!nready)continue;
		int conn=0;
		while(FD_ISSET(sfd,&rset)){
			nready--;
			bzero(buf,sizeof(buf));
			struct sockaddr_un peeraddr={0};
			socklen_t peerlen=sizeof(peeraddr);
			conn=my_accept(sfd,(struct sockaddr *)&peeraddr,&peerlen);
			if(conn<0)break;
			inf(peeraddr.sun_path);
			FD_SET(conn,&allset);
			if(conn>maxfd)maxfd=conn;
			for(i=0;i<getCount(conn_a);i++){
				if(-1==conn_a[i])conn_a[i]=conn;
			}
			break;
		}
		if(!nready)continue;
		for(i=0;i<FD_SETSIZE;i++){
			conn=conn_a[i];
			if(-1==conn)continue;
			while(FD_ISSET(conn,&rset)){
				nready--;
				bzero(buf,sizeof(buf));
				ret=un_read(conn,buf,sizeof(buf));
				if(ret<0)break;
				if(0==ret){
					war("client close:%d",conn_a[i]);
					FD_CLR(conn,&allset);
					conn_a[i]=-1;
					break;
				}
				inf("c2s:%s",buf);
				proc(conn,buf,sizeof(buf));
				break;
			}
			if(!nready)break;
		}
	}while(1);
}
void in_my_select_tcp_server(char *ip,in_port_t port,proc_t proc){
	size_t i=0;
	#define BUF_SIZE MSG_BUF_BYTE
	char buf[BUF_SIZE]="";
	int conn_a[FD_SETSIZE]={0};
	for(i=0;i<getCount(conn_a);i++)conn_a[i]=-1;
	int sfd=my_socket(AF_INET,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sfd)exit(-1);
	int ret=1;
	ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&ret,sizeof(ret));
	if(ret<0)exit(-1);
	ret=in_bind(sfd,ip,port);
	if(-1==ret)exit(-1);
	ret=my_listen(sfd,SOMAXCONN);
	if(-1==ret)exit(-1);
	int maxfd=sfd;
	fd_set rset={0},allset={0};
	FD_SET(maxfd,&allset);
	do{
		rset=allset;
		int nready=my_select(maxfd+1,&rset,NULL,NULL,NULL,NULL);
		if(nready<0){
			if(EINTR==errno)continue;//防止收到信号时退出
			show_errno(0,"my_select");
			exit(-1);
		}
		if(!nready)continue;
		int conn=0;
		while(FD_ISSET(sfd,&rset)){
			nready--;
			bzero(buf,sizeof(buf));
			struct sockaddr_in peeraddr={0};
			socklen_t peerlen=sizeof(peeraddr);
			conn=my_accept(sfd,(struct sockaddr *)&peeraddr,
				&peerlen);
			if(conn<0)break;
			inf("(peer)conn:%d ip:%s port:0x%4x",conn,
				inet_ntoa(peeraddr.sin_addr),peeraddr.sin_port);
			FD_SET(conn,&allset);
			if(conn>maxfd)maxfd=conn;
			for(i=0;i<getCount(conn_a);i++){
				if(-1==conn_a[i]){
					conn_a[i]=conn;break;
				}
			}
			break;
		}
		if(!nready)continue;
		for(i=0;i<FD_SETSIZE;i++){
			conn=conn_a[i];
			if(-1==conn)continue;
			while(FD_ISSET(conn,&rset)){
				nready--;
				bzero(buf,sizeof(buf));
				ret=un_read(conn,buf,sizeof(buf));
				if(ret<0)break;
				if(0==ret){
					war("client close:%d",conn_a[i]);
					FD_CLR(conn,&allset);
					conn_a[i]=-1;
					break;
				}
				inf("c:%d->s:%s",conn,buf);
				proc(conn,buf,sizeof(buf));
				break;
			}
			if(!nready)break;
		}
	}while(1);
}
#if 1
typedef struct in_serv_t{
	proc_t *pProc;		
	char *ip;
	in_port_t port;
	int fd;
}sock_serv_t;
void in_my_select_udp_server(in_serv_t tbl[],size_t count){
	size_t i=0;
	#define BUF_SIZE MSG_BUF_BYTE
	char buf[BUF_SIZE]="";
	fd_set rset={0},allset={0};
	for(i=0;i<count;i++){
		tbl[i].fd=my_socket(AF_INET,SOCK_DGRAM|SOCK_CLOEXEC,0);
		if(-1==tbl[i].fd)exit(-1);
		int ret=1;
		ret=setsockopt(tbl[i].fd,SOL_SOCKET,SO_REUSEADDR,
			&ret,sizeof(ret));
		if(ret<0)exit(-1);
		ret=in_bind(tbl[i].fd,tbl[i].ip,tbl[i].port);
		if(-1==ret)exit(-1);
		FD_SET(tbl[i].fd,&allset);
	}
	int maxfd=tbl[i-1].fd;
	FD_SET(maxfd,&allset);
	do{
		rset=allset;
		int nready=my_select(maxfd+1,&rset,NULL,NULL,NULL,NULL);
		if(nready<0){
			if(EINTR==errno)continue;//防止收到信号时退出
			exit(-1);
		}
		if(!nready)continue;	
		for(i=0;i<count;i++){
			if(-1==tbl[i].fd)continue;
			while(FD_ISSET(tbl[i].fd,&rset)){
				nready--;
				bzero(buf,sizeof(buf));
				ret=un_read(tbl[i].fd,buf,sizeof(buf));
				if(ret<0)break;
				if(0==ret){
					war("client close:%d",tbl[i].fd);
					FD_CLR(conn,&allset);
					tbl[i].fd=-1;
					break;
				}
				inf("c:%d->s:%s",conn,buf);
				proc(conn,buf,sizeof(buf));
				break;
			}
			if(!nready)break;
		}
	}while(1);
}
#endif