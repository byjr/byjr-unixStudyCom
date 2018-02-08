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
int main (int argc, char *argv[])
{
	int ret=0,i=0;
	for(i=SIGRTMIN;i<=SIGRTMAX;i++){
		signal(i,signal_handle);		
	}		
	log_init(NULL);
	ret=px_shm_get(&shm,SHM_NAME);
	if(ret<0)exit(-1);
	// sfd=my_socket(AF_UNIX,SOCK_DGRAM,0);
	sfd=my_socket(AF_INET,SOCK_DGRAM,0);	
	if(-1==sfd)exit(-1);
	// ret=un_bind(sfd,SOCKET_ADDR);
	// ret=un_connect(sfd,SOCKET_ADDR);
	ret=in_connect(sfd,5188,"127.0.0.1");
	if(-1==ret)exit(-1);	
	do{
		char snd_buf[1024]="",rcv_buf[1024]="";
		// struct sockaddr_un addr={AF_UNIX};
		struct sockaddr_in addr={AF_INET};
		socklen_t addr_len=sizeof(addr);	
		inf("input:")
		ret=scanf("%1024s",snd_buf);
		if(-1==ret)exit(-1);
		inf("snd:%s",snd_buf);
#define VERSION 0
		
#if VERSION ==0		
		ret=un_write(sfd,snd_buf,strlen(snd_buf));
		if(-1==ret)exit(-1);		
		ret=un_read(sfd,rcv_buf,sizeof(rcv_buf));
		if(-1==ret)exit(-1);
#elif VERSION ==1	
		ret=my_send(sfd,snd_buf,strlen(snd_buf),0);
		if(-1==ret)exit(-1);		
		ret=my_recv(sfd,rcv_buf,sizeof(rcv_buf),0);
		if(-1==ret)exit(-1);
#elif VERSION ==2	
		ret=my_sendto(sfd,snd_buf,strlen(snd_buf),0,NULL,0);
		if(-1==ret)exit(-1);		
		ret=my_recvfrom(sfd,rcv_buf,sizeof(rcv_buf),0,NULL,NULL);
		if(-1==ret)exit(-1);
#endif		
		inf("%d,%s/rcv:%s",VERSION,__FILE__,rcv_buf);		
	}while(1);
	while(1)pause();
	return 0;
}