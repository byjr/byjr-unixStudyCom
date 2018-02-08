#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <slog/slog.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "sv_sem.h"

int sv_semget(int *p_semid,int count,int proj_id)
{
	key_t key={0};
	if(-1==(key=ftok("/",proj_id))){
		err("ftok fail,errno:%d[%s].",errno,strerror(errno));
		return -1;  
	}
	if(-1==(*p_semid=semget(key, count,0666 | IPC_CREAT))){
		err("semget fail,errno:%d[%s].",errno,strerror(errno));
		return -2;  	
	}
	return 0;
}

int sv_semop(int semid,int n,int val)
{
	int ret=0;
	struct sembuf sops={0};
	sops.sem_num=n;
	sops.sem_op=val;
	sops.sem_flg=SEM_UNDO;	
	ret=semop(semid,&sops,1);
	if(-1==ret){
		err("semop fail,errno:%d[%s].",errno,strerror(errno));
		exit(-1);
	}
	return 0;
}
int sv_semop_nowait(int semid,int n,int val)
{
	int ret=0;
	struct sembuf sops={0};
	sops.sem_num=n;
	sops.sem_op=val;
	sops.sem_flg=IPC_NOWAIT|SEM_UNDO;	
	ret=semop(semid,&sops,1);
	if(-1==ret){
		err("semop_nowait fail,errno:%d[%s].",errno,strerror(errno));
	}
	return 0;
}
#if 0//未调通
int sv_semtimedop(int semid,int n,int val,int sec)
{
	int ret=0;
	struct timespec ts={0};
	ret=clock_gettime(CLOCK_REALTIME, &ts);
	if(-1==ret){
		err("clock_gettime fail,errno:%d[%s].",errno,strerror(errno));
	}
	ts.tv_sec+=sec;
	struct sembuf sops={0};
	sops.sem_num=n;
	sops.sem_op=val;
	sops.sem_flg=SEM_UNDO;
	do{
		ret=semtimedop(semid,&sops,1,&ts);
	}while(-1==ret && EINTR==errno);//中断打断就回来继续等待
	if(-1==ret){
		err("semtimedop fail,errno:%d[%s].",errno,strerror(errno));
	}
	return 0;
}
#endif
int sv_semset(int semid,int n,int val)
{  
	int ret=0;
    semun_t sem_union={0};
    sem_union.val = val;
	ret=semctl(semid,n,SETVAL,sem_union);
    if(-1==ret){
		err("semctl fail,errno:%d[%s].",errno,strerror(errno));
		exit(-1);
	}
    return 0;  
} 
int sv_semdel(int semid,int n)
{
	if(-1==semctl(semid,n,IPC_RMID, 0)){
		err("semctl IPC_RMID fail,errno:%d[%s].",errno,strerror(errno));
		return -1;  
	}
	return 0;
}
// --------------通用部分--------------------------<<

// --------------非通用部分------------------------<<