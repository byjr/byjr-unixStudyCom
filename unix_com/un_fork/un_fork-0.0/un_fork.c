#include "un_fork.h"
#include "string.h"
#include "lzl/misc.h"

pid_t my_clone(subFunc_t fn,void *args,int flag,size_t stack_size){
	void *stack = malloc(stack_size);
	if (stack == NULL){
		show_errno(0,"malloc");
		return -1;
	}	  
	void *stackTop = stack + stack_size;
	pid_t pid = clone(fn,stackTop,flag,args);
	if (pid <0){
		show_errno(0,"clone");
		return -2;		
	}
    return pid;
}

typedef struct arg_ct_t{
	char *arg;
	struct arg_ct_t* prev;
}arg_ct_t;
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
char** argl_to_argv(char argl[]){
	int i=0,count=0;
	char **argv=(char**)calloc(1,sizeof(char*));
	if(!argv)return NULL;
	argv[0]=argl;
	for(i=0;;i++){
		if(argl[i]==' '||argl[i]=='\0'){
			count++;
			argv=(char**)realloc(argv,count*sizeof(char *));
			if(!argv)return NULL;
			argv[count]=argl+i+1;
			char *arg=calloc(1,argv[count]-argv[count-1]);
			if(!arg)return NULL;
			strncpy(arg,argv[count-1],argv[count]-argv[count-1]-1);
			argv[count-1]=arg;
		}
	}
	return argv;
}
int vfexec(char *argl){
	char **argv=argl_to_argv(argl);
	if(!(argv && argv[1]))return -1;
	pid_t pid=vfork();
	if(pid<0)return -1;
	if(pid==0){
		dbg("sub process:%d",getpid());
		int ret=execv(argv[0],argv);
		if(ret<0)show_errno(0,"execv"),exit(-1);
	}
	int ws=0;
	pid=waitpid(-1,&ws,WNOHANG);
	inf("%d exited!",pid);	
	return 0;
}