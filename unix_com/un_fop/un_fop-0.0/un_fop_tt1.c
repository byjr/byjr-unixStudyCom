#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <lzl/slog.h>
#include <lzl/misc.h>
#include "un_fop.c"

#define TTEXT "3333"
int
main(int argc, char *argv[])
{
	int ret=0;
	char *text=NULL;
	log_init(NULL);
	// un_open(TPATH,O_CREAT|O_RDWR|O_EXCL,0666);
	// un_open("/tmp/tt1",O_CREAT|O_RDWR,0666);
	// un_unlink(TPATH);
	// ret=write_fstring(TPATH,TTEXT,strlen(TTEXT),"a");
	if(ret<0)return -1;
 	read_fstring(&text,TPATH);
	if(ret<0)return -1;
	inf(text);
	FREE(text);
	// un_unlink(TPATH);
	return 0;
}
