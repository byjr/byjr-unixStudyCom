#include "fifo_cmd.c"

int start_handle(void *args){
	inf(__func__);
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
fifo_cmd_t fifo_cmd_tbl[]={
	ADD_CMD_ITEM(start)
	ADD_CMD_ITEM(aget)
	ADD_CMD_ITEM(aset)
};

int main(int argc,char *argv[]){
	log_init("l=11111");
	
	int ret=fifo_cmd_init();
	if(ret<0)return -1;
	
	do{
		fifo_cmd_wait();
		fifo_cmd_proc(fifo_cmd_tbl,get_ar_count(fifo_cmd_tbl));
	}while(1);
}