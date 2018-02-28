#ifndef MISC_H_
#define MISC_H_
#include <errno.h>
#include <string.h>
#include "slog.h"
#define MISC_LOG_EN 0
#if MISC_LOG_EN
	#define err(x...) fprintf(stderr,x);fprintf(stderr,"\n");
	#define war(x...) fprintf(stderr,x);fprintf(stderr,"\n");
	#define dbg(x...) fprintf(stderr,x);fprintf(stderr,"\n");
	#define inf(x...) fprintf(stderr,x);fprintf(stderr,"\n");
#endif

#define show_error(ret, msg) \
	if(ret){\
		do {\
			err("%s failure,ret=%d",msg,ret);\
		}while(0);\
	}

#define FREE(x) ({ \
	if(x){ \
		free(x);x=NULL;\
	} \
})

#define IS_ARG_COUNT_LESS_THAN(x) \
	if(NULL==argv[x]){\
		err("args cann't less than %d!",x);\
		return -1;\
	}
	
#define get_ar_count(array) (sizeof(array)/sizeof(array[0]))
#define MIN(x,y,type) ({\
	type _x=x,_y=y;\
	_x<_y?_x:_y;\
})

#define MAX_COMMAND_LEN 1024

typedef struct misc_cmd_t{
	char *cmd;
	int (*handle)(void *);
}misc_cmd_t;

extern int exec_cmd(const char *cmd);
extern int exec_cmd2(const char *cmd, ...);
extern int exec_cmd3(char *rbuf, int rbuflen, const char *cmd, ...);
extern pid_t get_pid_by_name(char *pidName);
extern pid_t get_srv_pid(char *name_cli);
extern int write_str_to_file(char *path,char *str,char *mode);
extern int copy_file(char* dst_path,char *src_path);
extern int read_str_from_file(char **p_str,char *path,char *mode);
char** argl_to_argv(char argl[],char delim);
char *argv_to_argl(char *argv[],char delim);

#endif