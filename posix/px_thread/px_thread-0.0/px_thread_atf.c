#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include "px_thread.h"
#include <lzl/slog.h>
#include <lzl/misc.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *doit(void *arg){
	do{
		inf("%d/%ld is running...",getpid(),pthread_self());
		pthread_mutex_lock(&mutex);
		struct timespec ts = {2, 0};
		nanosleep(&ts, NULL);
		pthread_mutex_unlock(&mutex);
		// inf("%d/%ld end!",getpid(),pthread_self());		
	}while(1);
    return NULL;
}

void prepare(void){
    pthread_mutex_unlock(&mutex);
}

void parent(void){
    pthread_mutex_lock(&mutex);
}
void child(void){
    // doit(NULL);
}

int main(void){
	int ret=0;
	log_init(NULL);
	signal(SIGCHLD,SIG_IGN);
	dbg("%d/%ld is running...",getpid(),pthread_self());
    pthread_t tid;
    pthread_create(&tid, NULL, doit, NULL);
    pthread_atfork(prepare, parent, child);		
    struct timespec ts = {1, 0};
    nanosleep(&ts, NULL);
	ret=fork();
	switch(ret)	{
		//可以定义一些所有case 公用的变量
	case -1:
		show_errno(0,"fork");
		exit(-1);
	case 0://子进程
		war("%d/%ld is running...",getpid(),pthread_self());		
		// doit(NULL);
		break;
	default://父进程
		war("%d/%ld is running...",getpid(),pthread_self());
		// doit(NULL);
		break;				
	}
    px_thread_tryjoin(tid,NULL);
    dbg("%d/%ld end!",getpid(),pthread_self());
    return 0;
}