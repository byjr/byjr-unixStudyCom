#include <lzl/slog.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "un_signal.c"

typedef struct misc_cmd_t{
	char *cmd;
	int (*handle)(void *);
}misc_cmd_t;

void sig_handle(int signo)
{
	switch(signo){
	case SIGALRM ... SIGPROF:
		inf("handleed signal %d!",signo);
		break;	
	default:
		break;
	}
}
int setitimer_handle(void *args)
{
	char **argv=(char **)args;	
	int ret=0,type=0;
	if(argv[2]){
		switch(argv[2][0]){
		case '0':
			signal(SIGALRM,sig_handle);
			struct itimerval real_ctl={
				{2,0},//周期
				{1,0},//触发
			};
			un_setitimer(ITIMER_REAL,&real_ctl);
			inf("------------real_ctl");
			break;
		case '1':
			signal(SIGVTALRM,sig_handle);
			struct itimerval virtual_ctl={
				{2,0},//周期
				{1,0},//触发
			};
			un_setitimer(ITIMER_VIRTUAL,&virtual_ctl);
			inf("------------virtual_ctl");
			break;
		case '2':
			signal(SIGPROF,sig_handle);
			struct itimerval prof_ctl={
				{2,0},//周期
				{1,0},//触发
			};
			un_setitimer(ITIMER_PROF,&prof_ctl);
			inf("------------prof_ctl");
			break;			
		default:
			err("can't find the option!");
			break;
		}
	}
	do{
		//sleep(1);		
	}while(1);
	return 0;
}

void sa_routine(int signo,siginfo_t *info,void *context)
{
#if 0
	int arg=info->si_int;
	int arg1=info->si_value.sival_int;
	inf("signo:%d!",signo);
	inf("arg:%d!",arg);
	inf("arg1:%d!",arg1);
#else	
	char *date_str=info->si_ptr;
	inf("signo:%d!",signo);
	inf("date_str:%08xd!",date_str);
	if(context){
		inf("signal:%d recive date_str:%s",signo,date_str);
	}
#endif	
}
int sigaction_handle(void *args)
{
	char **argv=(char **)args;	
	int ret=0,type=0;
	struct sigaction sa={
		.sa_sigaction=sa_routine,
		.sa_flags=SA_SIGINFO,
	};
	un_sigaction(SIGUSR1,&sa);	
	do{
		sleep(1);		
	}while(1);
	return 0;
}
int sigqueue_handle(void *args)
{
	char **argv=(char **)args;	
	int ret=0;
	union sigval value={
		.sival_int=88,
	};
	un_sigqueue(argv[0],SIGUSR1,value);
	do{
		// sleep(1);		
	}while(0);
	return 0;
}
misc_cmd_t misc_cmd_tbl[]={
	{"setitimer",		setitimer_handle					},
	{"sigaction",		sigaction_handle					},
	{"sigqueue"	,		sigqueue_handle						},	
};
int main(int argc,char **argv)
{
	log_init(NULL);
	IS_ARG_COUNT_LESS_THAN(1);
	int i=0;
	int cmd_count=sizeof(misc_cmd_tbl)/sizeof(misc_cmd_tbl[0]);
	for(i=0;i<cmd_count;i++){
		if(!strcmp(argv[1],misc_cmd_tbl[i].cmd)){
			int ret=0;
			ret=misc_cmd_tbl[i].handle(argv);
			if(ret<0){
				return -2;
			}
			return 0;
		}
	}
	return -3;
}



