#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "fp_op.h"

int fp_read_str(char **p_str,char *path){
	int ret=0,fail=1;	
	FILE*fp=fp_open(path,"r");
	if(!fp)return -1;
	
	struct stat stat_buf;
	ret=fstat(fp->_fileno,&stat_buf);
	if(-1==ret)goto Exit1;
	
	char *str=(char*)calloc(1,stat_buf.st_size+1);
	if(!str)goto Exit1; 
	
	size_t ret_size=fp_read(str,1L,stat_buf.st_size,fp);
	if(ret_size<stat_buf.st_size){
		free(str);
		goto Exit1;
	}	
	*p_str=str;
	fail=0;
Exit1:
	fp_close(fp);
	if(fail)return -1;
	return 0;
}
int fp_write_str(char *path,char *str,size_t fsize){
	int ret=0;
	
	FILE*fp=fp_open(path,"w");
	if(!fp)return -1;
	
	size_t ret_size=fp_write(str,1L,fsize,fp);
	if(ret_size<fsize)return -1;
	return 0;	
}
