#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#define ARG_NUM 1
//#define log(fmt,args...) printf(fmt,##args)
#define log(x...) printf(x)
#define my_free(x){free(x);x=NULL;}
//	全局变量定义区
pthread_t tid_1,tid_2,tid_3;
sem_t sem1,sem2,sem3;

void* thread_1(){
	for(;;){
		sem_wait(&sem1);
		log("thread_1 get sem3!\r\n");
		sleep(1);
		sem_post(&sem2);
	}	
}   
void* thread_2(){
	for(;;){
		sem_wait(&sem2);
		log("thread_2 get sem1!\r\n");
		sleep(2);
		sem_post(&sem3);
	}	
}
void* thread_3(){
	for(;;){
		sem_wait(&sem3);
		log("thread_3 get sem2!\r\n");
		sleep(3);
		sem_post(&sem1);
	}		
}

int pthread_create_task(){	
	int ret=0;
	ret=pthread_create(&tid_1,NULL,thread_1,NULL);
	if(ret!=0)
		return -1;
	ret=pthread_create(&tid_2,NULL,thread_2,NULL);
	if(ret!=0)
		return -2;	
	ret=pthread_create(&tid_3,NULL,thread_3,NULL);
	if(ret!=0)
		return -3;					
	return 0;	
}
void pthread_init_sync(){
	sem_init(&sem1,0,1);
	sem_init(&sem2,0,0);
	sem_init(&sem3,0,0);
}
int main(int argc,char* argv[]){
	pthread_init_sync();
	if(pthread_create_task()!=0){
		log("creat thread fail!\r\n");
		return -1;
	}
	log("all thread creat seccess!\r\n");
	pthread_join(tid_1,NULL);
	pthread_join(tid_2,NULL);
	pthread_join(tid_3,NULL);
	
	return 0;
}