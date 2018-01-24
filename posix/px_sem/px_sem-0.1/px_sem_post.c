#include <slog/slog.h>
#include <unistd.h>
#include "px_sem.c"

char buf[MAX_BUF_SIZE]="";
int
main(int argc, char *argv[])
{
	unsigned int val=0;
	sem_t *pSlogSem=NULL;
	memset(log_ctrl_set,'1',sizeof(log_ctrl_set));	
	// px_semunlink(SLOG_SEM_PATH);	
	if(px_semopen(&pSlogSem,SLOG_SEM_PATH,1)<0){
		return -1;
	}
	while(1){
		fgets(buf,sizeof(buf)-1,stdin);
		px_sempost(pSlogSem,10);
		sleep(1);
	}
}
