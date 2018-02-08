#include <signal.h>
#include "px_cond.h"
#include <lzl/cs_cmd.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
int main(int argc,char *argv[]){
	pid_t pid_srv=0;
	log_init(NULL);
	cs_cmd_init(0);
	do{
		argv_to_argl(px_shm->cmd_buf,argv,sizeof(px_shm->cmd_buf));
		pid_srv=get_srv_pid(__FILE__);
		if(pid_srv>0){
			kill(pid_srv,SIG_CS_CMD);
		}
	}while(0);
	return 0;
}