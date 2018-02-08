#ifndef UN_SIGNAL_H_
#define UN_SIGNAL_H_ 1
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h> 
#include <sys/stat.h>
#include "un_fop.h"
#include "misc.h"
#include "slog.h"

#define FIFO_PATH 		"/tmp/cmd.fifo"
#define FIFO_BUF_SIZE 	1024

#define  un_mkfifo(path,mode) ({\
	int ret=mkfifo(path,mode);\
	if(-1==ret)show_errno(0,"un_mkfifo");\
	ret?-1:0;\
})

extern int un_fifo_init(char *);
extern int un_fifo_read(char *buf,size_t size);
extern int un_fifo_write_str(char *ptr);
extern int un_fifo_write(char *buf,size_t size);
#endif