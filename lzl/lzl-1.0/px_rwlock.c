#include "px_rwlock.h"

int px_rwlockattr_set(pthread_rwlockattr_t *p_attr)
{
	int ret=0;
	ret=pthread_rwlockattr_setpshared(p_attr,PTHREAD_PROCESS_SHARED);
	if(ret){
		show_error(ret,"pthread_rwlockattr_getpshared");
		return -1;
	}
	ret=pthread_rwlockattr_setkind_np(p_attr,PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
	if(ret){
		show_error(ret,"pthread_rwlockattr_getkind_np");
		return -2;		
	}
	return 0;	
}
int px_rwlockattr_show(pthread_rwlockattr_t *p_attr)
{
	int ret=0;
	int pshared=0;
	ret=pthread_rwlockattr_getpshared(p_attr,&pshared);
	if(ret){
		show_error(ret,"pthread_rwlockattr_getpshared");
		return -1;
	}
	if(pshared==PTHREAD_PROCESS_SHARED){
		inf("系统范围");
	}else if(pshared==PTHREAD_PROCESS_PRIVATE){
		inf("进程范围");
	}
	int pref=0;
	ret=pthread_rwlockattr_getkind_np(p_attr,&pref);
	if(ret){
		show_error(ret,"pthread_rwlockattr_getpshared");
		return -2;		
	}
	if(pref==PTHREAD_RWLOCK_PREFER_READER_NP){
		inf("读优先");
	}else if(pref==PTHREAD_RWLOCK_PREFER_WRITER_NP){
		inf("写优先");
	}else if(pref==PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP){
		inf("不递归");
	}
	return 0;
}


