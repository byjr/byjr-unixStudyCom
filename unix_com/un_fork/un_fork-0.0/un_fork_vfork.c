#include "un_fork.c"
int var=111;
int main(int argc, char *argv[]){
	log_init("l=11111");
	pid_t pid=vfork();
	if(pid<0)return -1;
	if(pid==0){
		dbg("sub process:%d",getpid());
		//execlp("ls","-l","-a",NULL );
		var=222;
		exit(0);
	}
	
	do{
		inf("sub process:%d",getpid());
		sleep(1);
	}while(1);
}