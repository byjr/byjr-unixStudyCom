#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include "un_fcntl.h"
#include <time.h>
#include <lzl/px_sem.h>
#include <lzl/px_thread.h>
#include <lzl/px_shm.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/cs_cmd.h>
#include <lzl/un_fop.h>
usr_shm_t *pxshm=NULL;
sem_t *p_sem=NULL;
pthread_t tid[]={0};
int fd=0;
int fd_ar[]={0,0};
int open_handle(void *args){
	char **argv=(char **)args;	
	fd_ar[0]=open(TEST_FILE_PATH,O_RDWR|O_CREAT|O_APPEND,0666);
	if(!fd_ar[0]){
        show_errno(errno,__func__);
		return -1;
	}	
	return 0;
}
int close_handle(void *args){
	char **argv=(char **)args;
	int ret=0;
	ret=close(fd);
	if(ret<0){
		show_errno(errno,__func__);
		return -1;		
	}
	return 0;		
}
int unlock_handle(void *args){
	char **argv=(char **)args;
	struct flock lock={0}; 
	int ret=0;
	ret=fcntl(fd,F_GETLK,&lock);
	if(ret<0){
		show_errno(errno,__func__);
		return -1;		
	}
	return 0;
}
int lock_handle(void *args){
	char **argv=(char **)args;
	
	return 0;
}
int update_lock_st(struct flock *p_lock,char *argv[]){
	// inf("%s,%s,%s,%s,%s,%s",argv[1],argv[2],argv[3],argv[4],argv[5],argv[6]);
	IS_ARG_COUNT_LESS_THAN(6);
	switch(argv[3][0]){
	case '0':
		p_lock->l_type = F_RDLCK;
		break;
	case '1':
		p_lock->l_type = F_WRLCK;
		break;
	case '2':
		p_lock->l_type = F_UNLCK;
		break;
	default:
		break;
	}
	switch(argv[4][0]){
	case '0':
		p_lock->l_whence = SEEK_SET; 
		break;
	case '1':
		p_lock->l_whence = SEEK_CUR; 
		break;
	case '2':
		p_lock->l_whence = SEEK_END; 
		break;
	default:
		break;		
	}
	p_lock->l_start=atoi(argv[5]);
	p_lock->l_len=atoi(argv[6]);
	p_lock->l_pid=-1;
}
void show_lock_info(struct flock *p_lock){
	switch(p_lock->l_type){
	case F_RDLCK:
		inf("l_type:F_RDLCK");
		break;
	case F_WRLCK:
		inf("l_type:F_WRLCK");
		break;
	case F_UNLCK:
		inf("l_type:F_UNLCK");
		break;
	default:
		inf("l_type:unkonow");
		break;
	}
	switch(p_lock->l_whence){
	case SEEK_SET:
		inf("l_whence:SEEK_SET");
		break;
	case SEEK_CUR:
		inf("l_whence:SEEK_CUR");
		break;
	case SEEK_END:
		inf("l_whence:SEEK_END");
		break;
	default:
		inf("l_whence:unkonow");
		break;
	}
	inf("l_start:%d",p_lock->l_start);
	inf("l_len:%d",p_lock->l_len);
	inf("l_pid:%d",p_lock->l_pid);	
}
int fctnl_handle(void *args){
	char **argv=(char **)args;
	int ret=0;	
	IS_ARG_COUNT_LESS_THAN(2);
	struct flock lock={0};	
	switch(argv[2][0]){// 0:F_GETLK 1:F_SETLK 2:F_SETLKW
	case '0':
		update_lock_st(&lock,argv);
		ret=fcntl(fd,F_GETLK,&lock);
		if(!ret)show_lock_info(&lock);			
		break;
	case '1':
		update_lock_st(&lock,argv);
		ret=fcntl(fd,F_SETLK,&lock);
		if(-1==ret)show_errno(0,"fcntl");
		// show_lock_info(&lock);		
		break;		
	case '2':
		update_lock_st(&lock,argv);
		ret=fcntl(fd,F_SETLKW,&lock);
		if(-1==ret)show_errno(0,"fcntl");
		// show_lock_info(&lock);			
		break;	
	default:
		err("can not find the option %c!",argv[2][0]);
		break;	
	}
	if(ret<0){
		show_errno(errno,__func__);
		return -1;		
	}	
	return 0;
}
int write_handle(void *args){
	char **argv=(char **)args;
	int ret=0;
	int len=strlen(argv[2]);
	ret=write(fd,argv[2],len);
	if(ret<0){
        show_errno(errno,__func__);
		return -1;
	}
	return 0;
}
char buf[LINE_BUF_LEN]="";
int read_handle(void *args){
	char **argv=(char **)args;
	int ret=0;
	ret=read(fd,buf,sizeof(buf));
	if(ret<0){
        show_errno(errno,__func__);
		return -1;
	}
	dbg(buf);
	return 0;
}
int unlink_handle(void *args){
	char **argv=(char **)args;
	int ret=0;
	ret=unlink(TEST_FILE_PATH);
	if(ret<0){
        show_errno(errno,__func__);
		return -1;
	}
	return 0;		
}
int usr0_handle(void *args){
	inf("fd_ar[0]=%d",fd_ar[0]);
	fd=fd_ar[0];
	return 0;		
}
int usr1_handle(void *args){
	inf("fd_ar[1]=%d",fd_ar[1]);
	fd=fd_ar[0];
	return 0;	
}
cs_cmd_t cs_cmd_tbl[]={
	ADD_CMD_ITEM(open)
	ADD_CMD_ITEM(close)
	ADD_CMD_ITEM(read)
	ADD_CMD_ITEM(write)
	ADD_CMD_ITEM(unlink)	
	ADD_CMD_ITEM(fctnl)
	ADD_CMD_ITEM(lock)
	ADD_CMD_ITEM(unlock)
	ADD_CMD_ITEM(usr0)
	ADD_CMD_ITEM(usr1)
};
typedef void *(*p_start_routine_t)(void *);
void *star_routine(void *args){
	struct timespec ts = {1,0};	
	fd_ar[1]=un_open(TEST_FILE_PATH,O_RDWR|O_CREAT|O_APPEND,0666);
	do{
		nanosleep(&ts, NULL);	
		// war("%s:%d/%ld is done",__func__,getpid(),pthread_self());		
	}while(1);
}
p_start_routine_t p_routine_array[]={
	&star_routine,
};
#define HEAD_SYRTING "head:"
int main(int argc,char **argv){
	int ret=0,i=0;
	log_init(NULL);
// tools_init_code begin: 
	fd_ar[0]=un_open(TEST_FILE_PATH,O_RDWR|O_CREAT|O_APPEND,0666);
	// char *f_content=NULL;
	// un_unlink(TEST_FILE_PATH);
	// ret=write_fstring(TEST_FILE_PATH,HEAD_SYRTING,sizeof(HEAD_SYRTING),"w");
	// if(ret<0)return -1;
	// ret=read_fstring(&f_content,TEST_FILE_PATH);  
	// inf(f_content);
	// FREE(f_content);
	for(i=0;i<get_ar_count(tid);i++){
		px_thread_create(&tid[i],NULL,p_routine_array[i],NULL);
	}	
// tools_init_code end//
	cs_cmd_init(SIGRTMIN);
	int count=get_ar_count(cs_cmd_tbl);
	do{
		cs_cmd_wait();
		cs_cmd_proc(cs_cmd_tbl,count,px_shm->cmd_buf);
		// inf(px_shm->cmd_buf);
	}while(1);
// tools_deinit_code:

	return 0;
}