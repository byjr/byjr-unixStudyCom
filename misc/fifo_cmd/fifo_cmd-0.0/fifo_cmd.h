#ifndef _FIFO_CMD_H
#define _FIFO_CMD_H
#include <stdlib.h>
#include <lzl/un_fifo.h>
#include <lzl/misc.h>
#include <lzl/slog.h>

#define ADD_CMD_ITEM(x) {#x,x##_handle},

#define FIFO_CMD_DELIM 	'/'
#define FIFO_CMD_ENDC 	'\n'

typedef struct fifo_cmd_t{
	char *cmd;
	int (*handle)(void *);
}fifo_cmd_t;

extern int fifo_cmd_init();
int fifo_cmd_wait(void);
extern int fifo_cmd_proc(void *table,int num);
#endif