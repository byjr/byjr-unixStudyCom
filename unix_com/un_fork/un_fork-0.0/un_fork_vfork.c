#include "un_fork.c"
char *cmd={
	"/bin/ping www.baidu.com -c 2",
	// "find ./ -name *.c",
	// "ls -l",
	// "/tmp/un_fork-0.0/un_fork_tls",
	// "tree ./",
};
void child_handle(int sig){
	int ws=0;
	int pid=waitpid(-1,&ws,WNOHANG);
	err("%s:%d exited!",__func__,pid);
}
int var=111;
int main(int argc, char *argv[]){
	log_init("l=11111");
	signal(SIGCHLD,child_handle);
	char *argl=argv_to_argl(argv,' ');
	if(!argv)return -1;
	int ret=vfexec(argl);
	// int ret=vfexec_nowait(argv[1]);
	if(ret<0)show_errno(0,"vfexec");
	war("child have return!")
	do{
		pause();
	}while(1);
	return 0;
}