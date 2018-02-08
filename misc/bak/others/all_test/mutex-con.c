#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#define ARG_NUM 1
//#define log(fmt,args...) printf(fmt,##args)
#define log(x...) printf(x)
//	全局变量定义区
pthread_t tid_1,tid_2,tid_3;

pthread_mutex_t mutex_1;

pthread_cond_t cond;

int var_1=0;

void* thread_1(){
	for(;;){
		//log("thread_1 is runing...\r\n");
		//pthread_cond_wait(&cond,&mutex_1);
		pthread_mutex_lock(&mutex_1);
		var_1++;
	}	
}   
void* thread_2(){
	for(;;){
		//log("thread_2 is runing...\r\n");			
		//pthread_mutex_lock(&mutex_1); 	
		//pthread_cond_wait(&cond,&mutex_1);
		//log("pthread_mutex_unlock(&mutex_1)--------!\r\n");
		//pthread_cond_wait(&cond,&mutex_1);
		pthread_mutex_lock(&mutex_1);
		var_1+=100;
	}	
}
void* thread_3(){
	for(;;){
		//log("thread_3 is runing...\r\n");
		log("var_1 current value is:%d\r\n",var_1);
		usleep(500000);		
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
	pthread_mutex_init(&mutex_1,NULL);	
	pthread_cond_init(&cond,NULL);
	pthread_mutex_lock(&mutex_1);
}
int main(int argc,char* argv[]){
	pthread_init_sync();
	if(pthread_create_task()!=0){
		log("creat thread fail!\r\n");
		return -1;
	}
	log("all thread creat seccess!\r\n");
	while(1){
		int a=0;
		scanf("%d",&a);
		a=0;
		pthread_mutex_unlock(&mutex_1);		
		pthread_cond_signal(&cond);
		//pthread_mutex_unlock(&mutex_1);				
		log("post a cond ----------------!\r\n");		
	}
	return 0;
}