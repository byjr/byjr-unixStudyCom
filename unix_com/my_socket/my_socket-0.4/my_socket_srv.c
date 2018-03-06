#include <signal.h>
#include <unistd.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/px_shm.h>
#include <lzl/un_fop.h>
#include "my_socket.c"
#define PREFIX ":s->c"
static int in_serv_proc(int conn){
	#define BUF_SIZE MSG_BUF_BYTE
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
	#define BUF_SIZE MSG_BUF_BYTE
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
static net_serv_t net_tbl[]={
	// {&in_serv_proc,"127.0.0.1",5188,0},
	// {&in_serv_proc,"127.0.0.1",5189,0},
	// {&in_serv_proc,"127.0.0.1",5190,0},
	{&un_serv_proc,"/tmp/cmd1.sock",0,0},
	{&un_serv_proc,"/tmp/cmd2.sock",0,0},
	{&un_serv_proc,"/tmp/cmd2.sock",0,0},
};
int main(int argc, char *argv[]){
	log_init("l=11111");
	// un_select_tcp_server(UN_SOCK_PATH,un_serv_proc);
	// in_select_tcp_server(SERVER_IP,PORT_NUM,in_serv_proc);
	// in_select_udp_server(net_tbl,getCount(net_tbl));
	un_select_udp_server(net_tbl,getCount(net_tbl));
}