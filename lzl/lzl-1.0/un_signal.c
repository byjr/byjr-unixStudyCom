#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include "misc.h"
#include "slog.h"
#include "un_signal.h"

int un_setitimer(int which, const struct itimerval *p_value)
{
	int ret=0;
	ret=setitimer(which,p_value,NULL);
	if(-1 == ret){
		show_error(ret,__func__);	
		return -1;
	}
	return 0;
}
int un_sigaction(int signum, const struct sigaction *p_act)
{
	int ret=0;
	ret=sigaction(signum,p_act,NULL);
	if(-1 == ret){
		show_error(ret,__func__);	
		return -1;
	}
	return 0;
}
int un_sigqueue(char *name, int sig, const union sigval value)
{
	int ret=0;
	if(!name){
		err("%s: name is NULL!");
		return -1;
	}
	pid_t pid=get_pid_by_name(name);
	if(pid <=0){
		err("get pid by name:%s fialure!",name);
		return -1;
	}
	inf("get %s's pid: %d!",name,pid);
	ret=sigqueue(pid,sig,value);
	if(ret<0){
		return -1;
	}
	return 0;
}


