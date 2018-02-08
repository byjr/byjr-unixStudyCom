#include "px_msgq.c"
#include <lzl/un_fop.h>
#include <fcntl.h> 
#include <unistd.h>
// misc_cmd_t misc_cmd_tbl[]={
	// {"snd",		snd_handle					},
	// {"rcv",		rcv_handle					},
	// {"set",		set_handle					},
	// {"ntf",		ntf_handle					},
// };
#define FIFO_PATH "/tmp/cmd.fifo"
#define CMD_BUF_SIZE 1024
char cmd_buf[CMD_BUF_SIZE]="";
int main(int argc,char **argv)
{
	log_init("l=11111");
	unlink(FIFO_PATH);
	int ret=mkfifo(FIFO_PATH,0777);
	if(-1==ret){
		show_errno(0,"mkfifo");
		return -1;		
	}
	int fifo_fd=un_open(FIFO_PATH,O_RDONLY|O_EXCL,0777);
	if(-1==fifo_fd) return -1;
	for(;;){
		memset(cmd_buf,0,sizeof(cmd_buf));
		size_t ret_size=un_read(fifo_fd,cmd_buf,sizeof(cmd_buf));
		if(ret_size<1) continue;
		inf("read from fifo :%s",cmd_buf);
	}	
}



