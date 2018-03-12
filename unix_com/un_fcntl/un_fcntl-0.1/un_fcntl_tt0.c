#include "un_fcntl.c"
#include <lzl/slog.h>
#include <lzl/un_fifo.h>
#define FIFO_PATH "/tmp/cmd.fifo"
int main(int argc,char* argv[]){
	log_init("l=11111");
	int ret=un_fifo_init(FIFO_PATH,"+");
	if(ret<0)return -1;
	char buf[FIFO_BUF_SIZE]="";
	int fd=getFifoFd();
	ret=fcntl(fd,F_GETFL,0);
	if(ret<0)return -1;
	ret=fcntl(fd,F_SETFL,ret|O_NONBLOCK);
	if(ret<0)return -1;
	do{
		ret=un_fifo_read(buf,sizeof(buf));
		inf("ret=%d",ret);
		if(ret<0)return -1;
		inf(buf);
	}while(1);	
}

	
		
