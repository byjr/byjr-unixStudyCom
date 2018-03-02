#include "px_thread.c"
void *start_routine(void *args){
	do{
		inf("sub_thread %08ld is running...",pthread_self());
		usleep(1000000*1);
	}while(1);
}	
pxThread_t trd_array[]={
	{start_routine,NULL,NULL,0},
	{start_routine,NULL,NULL,0},
	{start_routine,NULL,NULL,0},
	{start_routine,NULL,NULL,0},	
};
int main(int argc,char *argv[]){
	log_init("l=11111");
	int ret=px_thread_array_create(trd_array,getArrayCount(trd_array));
	if(ret<0)return -1;
	do{
		pause();
	}while(1);
}