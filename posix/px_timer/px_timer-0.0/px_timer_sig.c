#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "px_timer.h"
#include <lzl/slog.h>
#define CLOCKID CLOCK_REALTIME

void sig_handler(int signo){
	printf("timer_signal function! %d\n", signo);
}

int main(){
	log_init(NULL);
	struct timespec tvs={0,0.5*1000000000},tvs1={0};
	//XXX int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	// signum--指定的信号编号，可以指定SIGKILL和SIGSTOP以外的所有信号编号
	// act结构体--设置信号编号为signum的处理方式
	// oldact结构体--保存上次的处理方式
	//
	// struct sigaction 
	// {
	// void (*sa_handler)(int);			//信号响应函数地址
	// void (*sa_sigaction)(int, siginfo_t *, void *);   //但sa_flags为SA——SIGINFO时才使用
	// sigset_t sa_mask;         //说明一个信号集在调用捕捉函数之前，会加入进程的屏蔽中，当捕捉函数返回时，还原
	// int sa_flags;
	// void (*sa_restorer)(void);	//未用
	// };
	//
	timer_t timerid;
	struct sigevent evp={0};
#if 0
	struct sigaction act={0};
	act.sa_handler = sig_handler;
	act.sa_flags = 0;
	// XXX int sigaddset(sigset_t *set, int signum);  //将signum指定的信号加入set信号集
	// XXX int sigemptyset(sigset_t *set);			//初始化信号集	
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGUSR1, &act, NULL) == -1){
		perror("fail to sigaction");
		exit(-1);
	}
#else
	signal(SIGUSR1,sig_handler);
#endif	
	evp.sigev_signo = SIGUSR1;
	evp.sigev_notify = SIGEV_SIGNAL;
	if (timer_create(CLOCK_REALTIME, &evp, &timerid) == -1)	{
		perror("fail to timer_create");
		exit(-1);
	}
	struct itimerspec it={{2,0},{1,0}},itr={0};
	if (timer_settime(timerid, 0, &it, 0) == -1)	{
		perror("fail to timer_settime");
		exit(-1);	
	}
	do{
		timer_gettime(timerid,&itr);
		inf("itr:\n%ld\n%ld\n%ld\n%ld",
			itr.it_interval.tv_sec,
			itr.it_interval.tv_nsec,
			itr.it_value.tv_sec,
			itr.it_value.tv_nsec			
		);
		nanosleep(&tvs,NULL);
		// pause();
	}while(1);
	return 0;
}