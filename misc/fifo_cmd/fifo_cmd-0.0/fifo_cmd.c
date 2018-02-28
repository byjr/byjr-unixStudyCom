#include "fifo_cmd.h"
char fifo_cmd_buf[FIFO_BUF_SIZE]="";
int fifo_cmd_init(char *path){
	int ret=un_fifo_init(path,"+");
	if(ret<0)return -1;
	return 0;
}
int fifo_cmd_wait(void){
	size_t ret_size=un_fifo_read(fifo_cmd_buf,sizeof(fifo_cmd_buf));
	if(ret_size<1) return -1;
}

int fifo_cmd_proc(void *table,int num){
	fifo_cmd_t *tbl=(fifo_cmd_t *)table;
	int ret=-2,i=0;
	char **argv=argl_to_argv(fifo_cmd_buf,FIFO_CMD_DELIM);
	if(!argv[0])return -1;
	for(i=0;i<num;i++){
		ret=strncmp(tbl[i].cmd,argv[0],sizeof(tbl[i].cmd));
		if(!ret){
			ret=tbl[i].handle(argv);
			break;
		}
		ret=-2;
	}
	switch(ret){
	case 0:
		inf("%s excute succeed!",argv[0]);
		break;
	case -1:
		err("%s excute failure!",argv[0]);
		break;
	case -2:
		err("%s not found!",argv[0]);
		break;
	default:
		break;
	}
	char *argl=argv_to_argl(argv,'/');
	printf("--->:%s\n",argl);
	free(argl);
	for(i=0;argv[i];i++)FREE(argv[i]);
	FREE(argv);
	return ret;
}




