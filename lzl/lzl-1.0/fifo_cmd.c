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
static int free_ct(arg_ct_t* tail){
	arg_ct_t *p_node=tail,*p_old=NULL;
	p_node=p_old=tail;
	if(!tail)return 0;
	do{
		p_node=p_old->prev;
		FREE(p_old->arg);
		FREE(p_old);
		p_old=p_node;
	}while(p_node);
	return 0;
}

static int argv_to_argl(char argl[],char *argv[],int len){
	int i=0,rt_len=0,rt_idx=0;
	bzero(argl,len);
	for(i=0;;i++){
		if(!argv[i]){			
			return 0;
		}
		rt_len=strlen(argv[i]);
		rt_idx+=rt_len;				
		if(rt_idx+2>=len){
			err("argl no enough buf!");
			return -1;
		}
		strcat(argl,argv[i]);
		rt_idx++;
		strcat(argl,FIFO_CMD_SEPARATOR);		
	}
	return 0;
}

static char** argl_to_argv(char argl[]){
	int i=0;
	char *arg_head=NULL,*arg_tail=NULL,*arg=NULL,**argv=NULL;
	arg_ct_t *p_new=NULL,*p_node=NULL,*p_head=NULL;
	arg_head=arg_tail=argl;
	for(i=0;i<10;i++){
		arg_head=strstr(arg_tail,FIFO_CMD_SEPARATOR);
		if(!arg_head)break;
		int len=arg_head-arg_tail;
		p_new=calloc(1,sizeof(arg_ct_t));
		if(!p_new)goto Err0;
		arg=(char*)calloc(1,len+1);
		if(!arg)goto Err1;
		strncpy(arg,arg_tail,len);
		p_new->arg=arg;
		p_new->prev=p_node;
		p_node=p_new;
		arg_tail=arg_head+1;
	}
	argv=(char**)calloc(i+1,sizeof(char *));
	if(!argv)goto Err2;
	p_head=p_node;
	i++;
	while(--i){
		argv[i-1]=p_node->arg;
		p_node=p_node->prev;
	}
	arg_ct_t *t_node=NULL;
	for(p_node=p_head;p_node;){
		t_node=p_node;
		p_node=p_node->prev;
		FREE(t_node);
	}
	return argv;
Err2:
	FREE(arg);
Err1:
	FREE(p_new);
Err0:
	free_ct(p_node);
	return NULL;
}

int fifo_cmd_proc(void *table,int num){
	fifo_cmd_t *tbl=(fifo_cmd_t *)table;
	int ret=-2,i=0;
	char **argv=argl_to_argv(fifo_cmd_buf);
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
	for(i=0;argv[i];i++){
		FREE(argv[i]);
	}
	return ret;
}




