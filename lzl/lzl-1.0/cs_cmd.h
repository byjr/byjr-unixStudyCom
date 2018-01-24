#ifndef _CS_CMD_H
#define _CS_CMD_H
#include <signal.h>
#include "px_shm.h"

#define PX_SHM_NAME 	"/px_shm"

#define ADD_CMD_ITEM(x) {#x,x##_handle},

#define CS_CMD_SEPARATOR "#"

typedef struct arg_ct_t{
	char *arg;
	struct arg_ct_t* prev;
}arg_ct_t;

typedef struct cs_cmd_t{
	char *cmd;
	int (*handle)(void *);
}cs_cmd_t;

extern int cs_cmd_init(int);
int cs_cmd_wait(void);
extern char** argl_to_argv(char argl[]);
extern int argv_to_argl(char argl[],char *argv[],int len);
extern int cs_cmd_proc(void *table,int num,char* args);
extern usr_shm_t *px_shm;
#endif