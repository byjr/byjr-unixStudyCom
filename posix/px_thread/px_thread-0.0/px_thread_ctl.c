#include <lzl/cs_cmd.h>
#include <lzl/slog.h>
int main(int argc,char *argv[])
{
	cs_cmd_init(SIGRTMIN);
	do{
		argv_to_argl(px_shm->cmd_buf,argv,sizeof(px_shm->cmd_buf));
	}while(0);
	return 0;
}



