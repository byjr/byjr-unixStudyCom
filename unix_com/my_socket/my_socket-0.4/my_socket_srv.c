#include <signal.h>
#include <unistd.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/px_shm.h>
#include <lzl/un_fop.h>
#include "my_socket.c"

static int server_proc(int conn,char *msg,size_t size){
	snprintf(msg,size,"%s:serv->c%d",msg,conn);
	size_t ret=un_write(conn,msg,size);
	if(ret<0)return -1;
	return 0;
}
int main(int argc, char *argv[]){
	log_init("l=11111");
	// un_select_server(UN_SOCK_PATH,server_proc);
	in_select_tcp_server(SERVER_IP,PORT_NUM,server_proc);	
}