#include <signal.h>
#include <unistd.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/px_shm.h>
#include <lzl/un_fop.h>
#include "my_socket.c"
#define PREFIX ":s->c"
#define BUF_SIZE MSG_BUF_BYTE
static int in_serv_proc(int conn){
	char buf[BUF_SIZE]="";	
	struct sockaddr_in addr={AF_INET};
	socklen_t addr_len=sizeof(addr);				
	size_t ret=my_recvfrom(conn,buf,sizeof(buf),0,(struct sockaddr*)&addr,&addr_len);
	// size_t ret=un_read(conn,buf,sizeof(buf));
	if(ret<0)exit(-1);
	if(0==ret)return 1;
	inf("addr:%lu",addr.sin_addr.s_addr);
	inf("c:%d->s:%s",conn,buf);
	strncat(buf,PREFIX,sizeof(buf)-sizeof(PREFIX));
	ret=my_sendto(conn,buf,sizeof(buf),0,(struct sockaddr*)&addr,addr_len);
	// ret=un_write(conn,buf,sizeof(buf));
	if(-1==ret)exit(-1);
	return 0;
}
static int un_serv_proc(int conn){
	char buf[BUF_SIZE]="";	
	struct sockaddr_un addr={AF_UNIX};
	socklen_t addr_len=sizeof(addr);				
	size_t ret=my_recvfrom(conn,buf,sizeof(buf),0,(struct sockaddr*)&addr,&addr_len);
	// size_t ret=un_read(conn,buf,sizeof(buf));
	if(ret<0)exit(-1);
	if(0==ret)return 1;
	inf("addr:%s",addr.sun_path);
	inf("c:%d->s:%s",conn,buf);
	strncat(buf,PREFIX,sizeof(buf)-sizeof(PREFIX));
	ret=my_sendto(conn,buf,sizeof(buf),0,(struct sockaddr*)&addr,addr_len);
	// ret=un_write(conn,buf,sizeof(buf));
	if(-1==ret)exit(-1);
	return 0;
}
char buf[BUF_SIZE]="";	
struct sockaddr_in inAddr={AF_INET};
socklen_t inLen=sizeof(inAddr);
static int inReadCallback(int conn){
	bzero(buf,sizeof(buf));
	size_t ret=my_recvfrom(conn,buf,sizeof(buf),0,(struct sockaddr*)&inAddr,&inLen);
	// size_t ret=in_read(conn,buf,sizeof(buf));
	if(ret<0)exit(-1);
	if(0==ret)return 1;
	inf("addr:%lu",inAddr.sin_addr.s_addr);
	inf("c:%d->s:%s",conn,buf);
	return 0;
}
static int inWriteCallback(int conn){				
	strncat(buf,PREFIX,sizeof(buf)-sizeof(PREFIX));
	size_t ret=my_sendto(conn,buf,sizeof(buf),0,(struct sockaddr*)&inAddr,inLen);
	// size_t ret=in_write(conn,buf,sizeof(buf));
	if(ret<0)exit(-1);
	return 0;
}
struct sockaddr_un unAddr={AF_UNIX};
socklen_t unLen=sizeof(unAddr);
static int unReadCallback(int conn){
	bzero(buf,sizeof(buf));
	size_t ret=my_recvfrom(conn,buf,sizeof(buf),0,(struct sockaddr*)&unAddr,&unLen);
	// size_t ret=un_read(conn,buf,sizeof(buf));
	if(ret<0)return -1;
	if(0==ret)return 1;
	// inf("addr:%s",unAddr.sun_path);
	inf("c:%d->s:%s",conn,buf);
	return 0;
}
static int unWriteCallback(int conn){				
	strncat(buf,PREFIX,sizeof(buf)-sizeof(PREFIX));
	size_t ret=my_sendto(conn,buf,sizeof(buf),0,(struct sockaddr*)&unAddr,unLen);
	// size_t ret=un_write(conn,buf,sizeof(buf));
	if(ret<0)return -1;
	return 0;
}
static net_serv_t net_tbl[]={
	{&unReadCallback,&unWriteCallback,"127.0.0.1",5188,0},
	{&unReadCallback,&unWriteCallback,"127.0.0.1",5189,0},
	{&unReadCallback,&unWriteCallback,"127.0.0.1",5190,0},
	// {&unReadCallback,&unWriteCallback,"/tmp/cmd.sock1",0,0},
	// {&unReadCallback,&unWriteCallback,"/tmp/cmd.sock2",0,0},
	// {&unReadCallback,&unWriteCallback,"/tmp/cmd.sock3",0,0},
};
int main(int argc, char *argv[]){
	log_init("l=11111");
	// un_select_tcp_server(UN_SOCK_PATH,un_serv_proc);
	// in_select_tcp_server(SERVER_IP,PORT_NUM,in_serv_proc);
	// in_select_udp_server(net_tbl,getCount(net_tbl));
	// un_select_udp_server(net_tbl,getCount(net_tbl));	
	// un_epoll_tcp_server(&net_tbl[0]);
	// un_epoll_udp_server(net_tbl,getCount(net_tbl));
	in_epoll_udp_server(net_tbl,getCount(net_tbl));
	// in_epoll_tcp_server(&net_tbl[0]);
}