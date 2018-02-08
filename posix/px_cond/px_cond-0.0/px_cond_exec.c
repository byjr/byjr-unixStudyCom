#include <signal.h>
#include <pthread.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <ctype.h>
#include "px_cond.h"
#include <lzl/cs_cmd.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
int main(int argc,char *argv[]){
	int ret=0;
	log_init(NULL);
	do{
		char rlt[1024]="";
		ret=exe_cmd_get(rlt,sizeof(rlt),"ls -l");
		if(ret)show_error(ret,"exe_cmd_get");
		// inf(rlt);
		struct stat f_stat={0};
		int fd=0;
		#define TEST_FILE_PATH "/tmp/t.txt"
		fd=open(TEST_FILE_PATH,O_RDWR|O_CREAT|O_APPEND,0666);inf("");
		if(-1==ret)return -1;
		ret=fstat(fd,&f_stat);
		if(ret)return -1;
		inf("f_stat.st_size=%d",f_stat.st_size);
		close(fd);
	}while(0);
	return 0;
}