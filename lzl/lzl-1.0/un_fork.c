#include "un_fork.h"

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

int vfexec_nowait(char *argl){
	char **argv=argl_to_argv(argl,' ');
	// char *argv[]={
		// "tree",
		// NULL,
	// };
	// char *env[]={
		// "/bin:/usr/bin",
	// };
	if(!(argv && argv[0]))return -1;
	pid_t pid=vfork();
	if(pid<0)return -1;
	if(pid==0){
		// int ret=execv(argv[0],argv);
		// if(ret<0)show_errno(0,"execv"),exit(-1);	//须带路径
		
		int ret=execvp(argv[0],argv);
		if(ret<0)show_errno(0,"execv"),exit(-1);	
		
		// int ret=execvpe(argv[0],argv,env);
		// if(ret<0)show_errno(0,"execv"),exit(-1);	
		
		// int ret=execve(argv[0],argv,env);
		// if(ret<0)show_errno(0,"execv"),exit(-1);	//须带路径		
		
		// int ret=execvpe(argv[0],argv,env);
		// if(ret<0)show_errno(0,"execv"),exit(-1);	
		
		// int ret=execl("/bin/ls","ls",NULL);
		// if(ret<0)show_errno(0,"execv"),exit(-1);	//须带路径
		
		// int ret=execlp("tree","tree",NULL);
		// if(ret<0)show_errno(0,"execv"),exit(-1);	
		
		// int ret=execle("tree","tree",NULL,env);
		// if(ret<0)show_errno(0,"execv"),exit(-1);	//须带路径			
	}
	return 0;
}

int vfexec(char *argl){
	int ret=vfexec_nowait(argl);
	if(ret<0)return -1;	
	int ws=0;
	pid_t pid=waitpid(-1,&ws,WUNTRACED);	
	inf("%d exited!",pid);	
	return 0;
}
