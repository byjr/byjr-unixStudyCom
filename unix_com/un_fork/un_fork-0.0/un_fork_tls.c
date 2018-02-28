#include "un_fork.c"

int var=111;
static int childFunc(void *arg){
	var=222;
	do{
		inf("%s,pid:%d",__func__,var);
		sleep(1);
	}while(1);
	return 0;
}

int main(int argc, char *argv[]){
	log_init("l=11111");
	err("");
	pid_t pid=my_clone(childFunc,NULL,CLONE_THREAD|CLONE_SIGHAND|CLONE_VM,2*M_BYTE);
	if(pid<0) return -1;
	dbg("sub process:%d",pid);
	do{
		inf("%s,pid:%d",__func__,var);
		sleep(1);
	}while(1);
}