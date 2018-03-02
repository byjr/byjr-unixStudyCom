#include <signal.h>
#include <unistd.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/px_shm.h>
#include <lzl/un_fop.h>
#include "my_socket.c"
usr_shm_t *shm=NULL;
int sfd=0;
int conn_a[FD_SETSIZE]={0};
void signal_handle(int signo){
	int ret=0;
	switch(signo){	
	case 34:{
		int i=0;
		for(i=0;i<getArrayCount(conn_a);i++)raw("%d",conn_a[i]);
		break;
	}	
	default:
		inf("recive signal:%d!",signo);	
		break;
	}
}
struct sockaddr_un peeraddr={0};
socklen_t peerlen=sizeof(peeraddr);
char buf[1024]="";
int main (int argc, char *argv[])
{
	int ret=0,i=0;
	for(i=SIGRTMIN;i<=SIGRTMAX;i++){
		signal(i,signal_handle);
	}		
	log_init(NULL);
	ret=px_shm_get(&shm,SHM_NAME);	
	if(ret<0)exit(-1);
	for(i=0;i<getArrayCount(conn_a);i++)conn_a[i]=-1;
	sfd=my_socket(AF_UNIX,SOCK_STREAM|SOCK_CLOEXEC,0);
	if(-1==sfd)exit(-1);
	unlink(UN_SOCK_PATH);
	struct sockaddr_un sock_addr={AF_UNIX,UN_SOCK_PATH};
	ret=my_bind(sfd,(struct sockaddr *)&sock_addr,sizeof(sock_addr));
	if(-1==ret)exit(-1);
	ret=my_listen(sfd,5);
	if(-1==ret)exit(-1);
	int nready=0,conn=0;
	int maxfd=sfd;
	fd_set rset={0},allset={0};	
	FD_SET(maxfd,&allset);
	do{
		rset=allset;
		nready=select(maxfd+1,&rset,NULL,NULL,NULL);
		if(nready<0){
			if(EINTR==errno)continue;
			show_errno(0,"select");
			exit(-1);
		}
		if(!nready)continue;
		while(FD_ISSET(sfd,&rset)){
			nready--;
			bzero(&peeraddr,sizeof(peeraddr));
			conn=my_accept(sfd,(struct sockaddr *)&peeraddr,&peerlen);
			if(ret<0)break;
			inf(peeraddr.sun_path);
			FD_SET(conn,&allset);
			if(conn>maxfd)maxfd=conn;
			for(i=0;i<getArrayCount(conn_a);i++){
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
					inf("client close:%d",conn_a[i]);
					FD_CLR(conn,&allset);
					conn_a[i]=-1;
					break;
				}
				inf("c2s:%s",buf);
				strncat(buf,":s2c",sizeof(buf)-strlen(buf));
				ret=un_write(conn,buf,sizeof(buf));
				break;			
			}
			if(!nready)break;
		}
		if(!nready)continue;
		
	}while(1);
	while(1)pause();
	return 0;
}