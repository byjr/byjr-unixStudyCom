#include "fifo_cmd.c"
#undef FIFO_BUF_SIZE
#include "xxx.h"

int start_handle(void *args){
	char ** argv=(char **)args;
	int i=0;
	while(argv[i++]){
		inf("[%d]:%s",i-1,argv[i-1]);
	}
	return 0;
}
int aget_handle(void *args){
	inf(__func__);
	return 0;
}
int aset_handle(void *args){
	inf(__func__);	
	return 0;
}
static cmd_t cmd_tbl[]={
	ADD_CMD_ITEM(start)
	ADD_CMD_ITEM(aget)
	ADD_CMD_ITEM(aset)
};

int main(int argc,char *argv[]){
	log_init("l=11111");
	#define CMD_FIFO "/tmp/cmd.fifo"
	fifo_cmd_proc(CMD_FIFO,cmd_tbl,getCount(cmd_tbl));
	return 0;
}