#include <signal.h>
#include <unistd.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/px_shm.h>
#include <lzl/un_fop.h>
#include "my_socket.c"
#define PREFIX ":s->c"
static int server_proc(int conn,char *msg,size_t size){
	strncat(msg,PREFIX,size-sizeof(PREFIX));
	size_t ret=un_write(conn,msg,size);
	if(ret<0)return -1;
	return 0;
}
static int udp_serv_proc(int conn,char *msg,size_t size){
	struct sockaddr_in addr={AF_INET};
	socklen_t addr_len=sizeof(addr);				
	size_t ret=my_recvfrom(conn,msg,size,0,(struct sockaddr*)&addr,&addr_len);
	if(ret<0)exit(-1);
	if(0==ret)return 1;
	inf("c:%d->s:%s",conn,msg);
	strncat(msg,PREFIX,size-sizeof(PREFIX));
	ret=my_sendto(conn,msg,size,0,(struct sockaddr*)&addr,addr_len);
	if(-1==ret)exit(-1);
	return 0;
}
static in_serv_t in_tbl[]={
	{&udp_serv_proc,"127.0.0.1",5188,0},
	{&udp_serv_proc,"127.0.0.1",5189,0},
	{&udp_serv_proc,"127.0.0.1",5190,0},
};
int main(int argc, char *argv[]){
	log_init("l=11111");
	// un_select_server(UN_SOCK_PATH,server_proc);
	// in_select_tcp_server(SERVER_IP,PORT_NUM,server_proc);
	in_select_udp_server(in_tbl,getCount(in_tbl));
}