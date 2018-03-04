#ifndef _FIFO_CMD_H
#define _FIFO_CMD_H
#include <stdlib.h>
#include "un_fifo.h"
#include "misc.h"
#include "slog.h"

#define FIFO_BUF_SIZE 	1024
#define FIFO_CMD_DELIM 	'/'

#define ADD_CMD_ITEM(x) {#x,x##_handle},

extern void fifo_cmd_proc(char* path,void *tbl,size_t count);
#endif