#include "fifo_cmd.h"

typedef struct cmd_t{
	char *cmd;
	int (*handle)(void *);
}cmd_t;

#define BUF_SIZE FIFO_BUF_SIZE
static char cmd_buf[BUF_SIZE]="";

static int cmd_init(char *path){
	int ret=un_fifo_init(path,"+");
	if(ret<0)return -1;
	return 0;
}
static int cmd_wait(void){
	memset(cmd_buf,0,sizeof(cmd_buf));
	size_t ret_size=un_fifo_read(cmd_buf,sizeof(cmd_buf));
	if(ret_size<1) return -1;
}

static int cmd_proc(cmd_t *tbl,size_t count){
	int ret=-2;
	#define CMD_DELIM FIFO_CMD_DELIM
	char **argv=argl_to_argv(cmd_buf,CMD_DELIM);
	if(!argv[0])return -1;
	size_t i=0;
	for(i=0;i<count;i++){
		ret=strncmp(tbl[i].cmd,argv[0],sizeof(tbl[i].cmd));
		if(!ret){
			ret=tbl[i].handle(argv);
			break;
		}
		ret=-2;
	}
	if(0==ret)		{inf("%s excute succeed!",argv[0]);}
	else if(-1==ret){err("%s excute failure!",argv[0]);}
	else if(-2==ret){err("%s not found!"	 ,argv[0]);}
	FREE(argv);
	return ret;
}
void fifo_cmd_proc(char* path,void *tbl,size_t count){
	unlink(path);
	int ret=cmd_init(path);
	if(ret<0)exit(-1);
	do{
		cmd_wait();
		clog(Hpurple,"%05d/%016ld get cmd:[%s]",
					getpid(),pthread_self(),cmd_buf);
		cmd_proc(tbl,count);
	}while(1);
}