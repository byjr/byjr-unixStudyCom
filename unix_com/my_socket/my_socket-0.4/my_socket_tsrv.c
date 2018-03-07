#include "my_socket.c"    
#define PREFIX ":s->c"
int main(int argc, char *argv[]){ 
	int sfd=my_socket(AF_UNIX,SOCK_DGRAM,0);
	if(-1==sfd)exit(-1);
	unlink(UN_SOCK_PATH);
	int ret=un_bind(sfd,UN_SOCK_PATH);
	if(-1==sfd)exit(-1);
	struct sockaddr_un addr={AF_UNIX};
	socklen_t addr_len=sizeof(addr);	
	do{
		ret=my_recvfrom(conn,buf,sizeof(buf),0,(struct sockaddr*)&addr,&addr_len);
		if(ret<0)exit(-1);
		inf("addr:%s",addr.sun_path);
		inf("c:%d->s:%s",conn,buf);	
		strncat(buf,PREFIX,sizeof(buf)-sizeof(PREFIX));
		ret=my_sendto(conn,buf,sizeof(buf),0,(struct sockaddr*)&addr,addr_len);
		if(ret<0)exit(-1);
	}while(1);
    return 0;        
}