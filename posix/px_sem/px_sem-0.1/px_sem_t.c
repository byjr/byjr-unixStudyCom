#include <slog/slog.h>
#include <unistd.h>
#include "px_sem.c"

int
main(int argc, char *argv[])
{
	unsigned int val=0;
	sem_t *p_slog_sem=NULL;
	px_semunlink(SLOG_SEM_PATH);	
	if(px_semopen(&p_slog_sem,SLOG_SEM_PATH,1)<0){
		return -1;
	}
	unsigned int v=0;
	sem_getvalue(p_slog_sem,&v);
	inf("%d",v);
//	px_seminit(&slog_sem,0,1);
	inf("px_semopen succeed!");
	px_semgetvalue(&val,p_slog_sem);
	while(1){
		//px_semwait(p_slog_sem);
		// px_sempost(&slog_sem,1);
		inf("--------------------------%d------------",argv[1][0]);
		// px_semwait(&slog_sem);
		//px_sempost(p_slog_sem,1);
		usleep(500*1000);
	}
}
