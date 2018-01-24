#include <slog/slog.h>

#include <unistd.h>
#include "px_sem.c"

int
main(int argc, char *argv[])
{
#if 1
	clog(Hred,"11111111111");
	clog(Hgreen,"11111111111");
	clog(Hyellow,"11111111111");
#else	
	sem_t *pSlogSem=NULL;	
	memset(log_ctrl_set,'1',sizeof(log_ctrl_set));
	int ret=0;
	struct timespec tsv={30,0};
	if(px_semopen(&pSlogSem,SLOG_SEM_PATH,1)<0){
		return -1;
	}
	while(1){
		// ret=px_semtimedwait(pSlogSem,tsv);
		// ret=px_semwait(pSlogSem);
		ret=px_semtrywait(pSlogSem);		
		if(ret<0)return -1;
		war("sem wait succeed!");
		sleep(1);
	}
#endif	
}
