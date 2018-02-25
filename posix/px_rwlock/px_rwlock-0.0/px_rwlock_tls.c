#include "px_rwlock.c"
#include <stdlib.h>
#include <lzl/px_shm.h>

pthread_rwlockattr_t rwlockattr={0};
pthread_rwlock_t rwlock={0};
int aget_handle(void *args){
	int ret=0;
	ret=px_rwlockattr_show(&rwlockattr);
	if(ret)return -1;
	return 0;
}
int aset_handle(void *args){
	int ret=0;
	ret=px_rwlockattr_set(&rwlockattr);
	if(ret)return -1;
	return 0;
}
cs_cmd_t cs_cmd_tbl[]={
	ADD_CMD_ITEM(aget)
	ADD_CMD_ITEM(aset)
};
int main(int argc,char **argv){
	int ret=0;
	log_init(NULL);
// tools_init_code:
	px_rwlockattr_init(&rwlockattr);
	cs_cmd_init(SIGRTMIN);
	int count=sizeof(cs_cmd_tbl)/sizeof(cs_cmd_tbl[0]);
	do{
		cs_cmd_wait();
		war("px_thread %08ld is running...",pthread_self());
		cs_cmd_proc(cs_cmd_tbl,count,px_shm->cmd_buf);
	}while(1);
// tools_deinit_code:
	pthread_rwlockattr_destroy(&rwlockattr);
	return 0;
}