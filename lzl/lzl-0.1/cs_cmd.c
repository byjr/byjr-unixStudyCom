#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <signal.h>
#include "cs_cmd.h"
#include "px_sem.h"
#include "misc.h"
#include "slog.h"

usr_shm_t *px_shm=NULL;
static sem_t cmd_sem={0};

static void 
cmd_sig_handle(int n){
	px_sempost(&cmd_sem,1);
}

int cs_cmd_init(int sig)
{
	int ret=0;
	if(sig){
		if(SIG_ERR==signal(sig,cmd_sig_handle)){
			show_errno(0,"signal");
			exit(-2);
		}		
	}
	px_shm_get(&px_shm,PX_SHM_NAME);
	ret=px_seminit(&cmd_sem,0,0);
	if(ret<0)exit(-1);
	return 0;
}
int cs_cmd_wait(void)
{
	px_semwait(&cmd_sem);
}
static int 
free_ct(arg_ct_t* tail){
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

int argv_to_argl(char argl[],char *argv[],int len)
{
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
		strcat(argl,CS_CMD_SEPARATOR);		
	}
	return 0;
}

char** argl_to_argv(char argl[])
{
	int i=0;
	char *arg_head=NULL,*arg_tail=NULL,*arg=NULL,**argv=NULL;
	arg_ct_t *p_new=NULL,*p_node=NULL,*p_head=NULL;
	arg_head=arg_tail=argl;
	for(i=0;i<10;i++){
		arg_head=strstr(arg_tail,CS_CMD_SEPARATOR);
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

int cs_cmd_proc(void *table,int num,char* args)
{
	cs_cmd_t *tbl=(cs_cmd_t *)table;
	int ret=-2,i=0;
	char **argv=NULL;
	argv=argl_to_argv(args);
	// inf("%s,%s,%s,%s,%s,%s",argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
	if(!argv[0])return -1;
	IS_ARG_COUNT_LESS_THAN(1);
	for(i=0;i<num;i++){
		ret=strncmp(tbl[i].cmd,argv[1],sizeof(tbl[i].cmd));
		if(!ret){
			ret=tbl[i].handle(argv);
			break;
		}
		ret=-2;
	}
	switch(ret){
	case 0:
		inf("%s excute succeed!",argv[1]);
		break;
	case -1:
		err("%s excute failure!",argv[1]);
		break;
	case -2:
		err("%s not found!",argv[1]);
		break;
	default:
		break;
	}
	for(i=0;argv[i];i++){
		FREE(argv[i]);
	}
	return ret;
}




