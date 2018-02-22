#include "un_fifo.c"
#include <stdlib.h>
#include <signal.h>
#include <lzl/px_thread.h>
char cmd_buf[FIFO_BUF_SIZE]="";
pthread_t tida[]={0};
char send_buf[FIFO_BUF_SIZE]="";
void show_buf(char *buf,size_t size){
	int i=0;
	inf("buf content is :");
	for(i=0;i<size;i++){
		raw("0x%02x,",buf[i]);
	}
	raw("\n");
}
void* start_routine(void *args){
	for(;;){
		memset(send_buf,0,sizeof(send_buf));	
		fgets(send_buf,sizeof(send_buf),stdin);
		size_t ret=un_fifo_write_str(send_buf);
		if(ret<0) return NULL;		
	}
}
int main(int argc,char **argv)
{
	log_init("l=11111");
	un_fifo_init("+");
	int ret=px_thread_create(&tida[0],NULL,&start_routine,NULL);
	if(ret<0)return -1;
	for(;;){
		memset(cmd_buf,0,sizeof(cmd_buf));
		int ret=un_fifo_read(cmd_buf,sizeof(cmd_buf));
		if(ret<0) continue;
		inf("read from fifo :%s",cmd_buf);
	}	
}