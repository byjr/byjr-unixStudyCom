#include <signal.h>
#include <lzl/cs_cmd.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
int main(int argc,char *argv[]){
	pid_t pid_srv=0;
	cs_cmd_init(0);
	do{
		argv_to_argl(px_shm->cmd_buf,argv,sizeof(px_shm->cmd_buf));
		pid_srv=get_srv_pid(__FILE__);
		inf("pid_srv:%d",pid_srv);
		if(pid_srv>0){
			kill(pid_srv,SIGRTMIN);
		}
	}while(0);
	return 0;
}