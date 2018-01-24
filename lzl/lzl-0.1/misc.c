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
#include "misc.h"
#include "slog.h"

static  pthread_mutex_t popen_mtx = PTHREAD_MUTEX_INITIALIZER;
int exec_cmd(const char *cmd)
{
	char buf[MAX_COMMAND_LEN];
	FILE *pfile;
	int status = -2;

	pthread_mutex_lock(&popen_mtx);
	if ((pfile = popen(cmd, "r"))) {
		fcntl(fileno(pfile), F_SETFD, FD_CLOEXEC);
		while (!feof(pfile)) {
			fgets(buf, sizeof buf, pfile);
		}
		status = pclose(pfile);
	}
	pthread_mutex_unlock(&popen_mtx);
	if (WIFEXITED(status)) {
		return WEXITSTATUS(status);
	}
	return -1;
}

int exec_cmd2(const char *cmd, ...)
{
	char buf[MAX_COMMAND_LEN];
	va_list args;

	va_start(args, (char *)cmd);
	vsnprintf(buf, sizeof(buf), cmd, args);
	va_end(args);

	return exec_cmd(buf);
}

int exec_cmd3(char *rbuf, int rbuflen, const char *cmd, ...)
{
	char buf[MAX_COMMAND_LEN];
	va_list args;
	FILE *pfile;
	int status = -2;
	char *p = rbuf;

	rbuflen = (!rbuf) ? 0 : rbuflen;

	va_start(args, (char *)cmd);
	vsnprintf(buf, sizeof(buf), cmd, args);
	va_end(args);

	pthread_mutex_lock(&popen_mtx);
	if ((pfile = popen(buf, "r"))) {
		fcntl(fileno(pfile), F_SETFD, FD_CLOEXEC);
		while (!feof(pfile)) {
			if ((rbuflen > 0) && fgets(buf, MIN(rbuflen, sizeof(buf),size_t), pfile)) {
				int len = snprintf(p, rbuflen, "%s", buf);
				rbuflen -= len;
				p += len;
			}
			else {
				break;
			}
		}
		if ((rbuf) && (p != rbuf) && (*(p - 1) == '\n')) {
			*(p - 1) = 0;
		}
		status = pclose(pfile);
	}
	pthread_mutex_unlock(&popen_mtx);
	if (WIFEXITED(status)) {
		return WEXITSTATUS(status);
	}
	return -1;
}

pid_t get_pid_by_name(char *pidName){
	char filename[256];
	char name[128];
	struct dirent *next;
	FILE *file;
	DIR *dir;
	pid_t retval = -1;

	dir = opendir("/proc");
	if (!dir) {
		perror("Cannot open /proc\n");
		return 0;
	}
	while ((next = readdir(dir)) != NULL) {
		/* Must skip ".." since that is outside /proc */
		if (strcmp(next->d_name, "..") == 0)
			continue;

		/* If it isn't a number, we don't want it */
		if (!isdigit(*next->d_name))
			continue;

		memset(filename, 0, sizeof(filename));
		sprintf(filename, "/proc/%s/status", next->d_name);
		if (!(file = fopen(filename, "r")))
			continue;

		memset(filename, 0, sizeof(filename));
		if (fgets(filename, sizeof(filename) - 1, file) != NULL) {
			/* Buffer should contain a string like "Name:   binary_name" */
			sscanf(filename, "%*s %s", name);
			/* Notice: the max size of stat is 15 */
			if (!strcmp(name, pidName)) {
				retval = strtol(next->d_name, NULL, 0);
			}
		}
		fclose(file);
		if (retval > 0) {
			break;
		}
	}
	closedir(dir);
	return retval;
}
pid_t get_srv_pid(char *name_cli)
{
	char srv_tail[4]="srv";
	char *name_srv=NULL;
	name_srv=strdup(name_cli);
	if(!name_srv)return -1;
	char *p_idx=NULL;
	p_idx=strstr(name_srv,"cli.c");
	if(!p_idx)return -1;
	memcpy(p_idx,srv_tail,sizeof(srv_tail));
	pid_t pid_srv=0;	
	pid_srv=get_pid_by_name(name_srv);
	FREE(name_srv);
	return pid_srv;
}
int write_str_to_file(char *path,char *str,char *mode){
	int fail=1,ret=0,len=0;
	FILE *fd=NULL;
	if(!str){
		err("str==NULL");
		goto Err0;
	}
	if(!(fd=fopen(path,mode))){
		err("fopen %s fail,err:%d[%s]",path,errno,strerror(errno));
		goto Err0;
	}
	if((len=strlen(str))<1){
		war("str content is empty!");
		goto Err1;
	}
	if((ret=fwrite(str,sizeof(char),len,fd))<len){
		err("fwrite %s fail,err:%d[%s]",path,errno,strerror(errno));
		goto Err1;		
	}
	fail=0;
Err1:
	fclose(fd);
Err0:
	if(fail)return -1;
	return 0;
}

int copy_file(char* dst_path,char *src_path)
{
	char *str=NULL;
	int fail=1;
	if(read_str_from_file(&str,src_path,"r")<0){		
		goto exit0;
	}
	if(write_str_to_file(dst_path,str,"w")<0){
		goto exit1;
	}
	fail=0;
exit1:
	FREE(str);
exit0:
	if(fail)return -1;
	return 0;
}
int read_str_from_file(char **p_str,char *path,char *mode)
{
	FILE *fd=NULL;
	int ret=0,fail=1;
	char *str=NULL;
	struct stat f_stat={0};
	if(!(fd=fopen(path,mode))){
		war("fopen %s fail,err:%d[%s]",path,errno,strerror(errno));
		goto Err0;
	}
	if((ret=stat(path,&f_stat))<0){
		err("stat %s fail,err:%d[%s]",path,errno,strerror(errno));
		goto Err1;
	}
	if(!(str=(char*)calloc(1,f_stat.st_size+1))){
		err("calloc fail!");
		goto Err1;
	}
	if((ret=fread(str,sizeof(char),f_stat.st_size,fd))<f_stat.st_size){
		err("fread %s fail,err:%d[%s]",path,errno,strerror(errno));
		goto Err2;		
	}
	if(!str){
		err("fread str fial!");
		goto Err2;
	}
	*p_str=str;
	fail=0;
Err2:
	if(fail)FREE(str);
Err1:
	fclose(fd);
Err0:
	if(fail)return -1;
	return 0;
}
