#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "un_fop.h"
#include "misc.h"
#include "slog.h"

int get_fsize(size_t *p_size,int fd)
{
	struct stat stat={0};
	int ret=un_fstat(&stat,fd);
	if(ret<0)return -1;
	*p_size=stat.st_size;
	// inf("file size =%d",*p_size);
	return 0;
}
void show_every_byte(char *buf,size_t size)
{
	int i=0;
	inf("buf show begin:------\\");
	for(i=0;i<size;i++){
		raw("%02d:0x%02x\n",i,buf[i]);
	}
	inf("buf show end:--------/");
}
int get_psize(size_t *p_size,char *path)
{
	struct stat lstat={0};
	int ret=stat(path,&lstat);
	if(ret<0)return -1;
	*p_size=lstat.st_size;
	return 0;
}
int read_fstring(char **p_buf,char *path)
{
	int ret=0;
	int fd=0,fail=1;
	fd=un_open(path,O_CREAT|O_RDONLY,0666);
	if(-1==fd)return -1;
	ssize_t size=0;
	ret=get_fsize(&size,fd);
	// ret=get_psize(&size,path);	
	if(ret<0)goto exit1;
	char *buf=(char *)calloc(1,size+1);
	if(!buf)goto exit1;	
	ret=(int)un_read(fd,buf,size);
	if(ret<0){
		FREE(buf);
		goto exit1;
	}
	show_every_byte(buf,size);
	*p_buf=buf;
	fail=0;
exit1:
	un_close(fd);
	if(fail)return -1;
	return 0;
}
int write_fstring(char *path,char *buf,ssize_t size,char *op)
{
	size_t ret_size=0;
	int fd=0,fail=1,ret=0;
	int flags=O_CREAT|O_RDWR;
	if('a'==op[0])flags|=O_APPEND;
	if('w'==op[0])flags|=O_TRUNC;
	fd=un_open(path,flags,0666);
	if(-1==fd)return -1;
	ret_size=un_write(fd,buf,size);
	if(ret_size<size)goto exit1;	
	fail=0;
exit1:
	ret=un_close(fd);
	if(-1==ret)return -1;
	if(fail)return -1;
	return 0;	
}
