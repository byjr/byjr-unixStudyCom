#include <signal.h>
#include <unistd.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/px_shm.h>
#include <lzl/un_fop.h>
#include "my_socket.c"
usr_shm_t *shm=NULL;
int sfd=0;
void signal_handle(int signo){
	int ret=0;
	switch(signo){	
	case 34:{
		
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
int conn_a[FD_SETSIZE]={0};
int main (int argc, char *argv[])
{
	int ret=0,i=0;
	for(i=SIGRTMIN;i<=SIGRTMAX;i++){
		signal(i,signal_handle);
	}		
	log_init(NULL);
	int nready=0;
	int maxfd=0;
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
		while(FD_ISSET(0,&rset)){
			nready--;
			bzero(buf,sizeof(buf));
			ret=un_read(0,buf,sizeof(buf));
			if(ret<0)break;
			inf(buf);break;
		}
	}while(1);
	while(1)pause();
	return 0;
}