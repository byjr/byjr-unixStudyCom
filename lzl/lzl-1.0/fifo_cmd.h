#ifndef _FIFO_CMD_H
#define _FIFO_CMD_H
#include <stdlib.h>
#include "un_fifo.h"
#include "misc.h"
#include "slog.h"

#define ADD_CMD_ITEM(x) {#x,x##_handle},

#define FIFO_CMD_DELIM '/'

typedef struct fifo_cmd_t{
	char *cmd;
	int (*handle)(void *);
}fifo_cmd_t;

extern int fifo_cmd_init(char *);
int fifo_cmd_wait(void);
extern int fifo_cmd_proc(void *table,int num);
#endif