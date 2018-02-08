#include "un_fifo.c"
#include <stdlib.h>
#include <signal.h>
char cmd_buf[FIFO_BUF_SIZE]="";
int main(int argc,char **argv)
{
	log_init("l=11111");
	un_fifo_init("+");
	for(;;){
		memset(cmd_buf,0,sizeof(cmd_buf));
		int ret=un_fifo_read(cmd_buf,sizeof(cmd_buf));
		if(ret<0) continue;
		inf("read from fifo :%s",cmd_buf);
	}	
}