#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include "un_lock.h"
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
int un_lock_get(short type,off_t start,off_t len){
	int ret=0;
	ret=fcntl(fd,F_GETLK,&lock);
	if(-1==ret){
		show_errno(0,__func__);
	}
	return 0;
}
int un_lock_set(){
	int ret=0;
	ret=fcntl(fd,F_GETLK,&lock);
	if(-1==ret){
		show_errno(0,__func__);
	}
	return 0;
}
int un_lock_un(){
	
	retrn 0;
}
	
		
