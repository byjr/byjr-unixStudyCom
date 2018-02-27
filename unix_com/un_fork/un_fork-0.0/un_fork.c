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