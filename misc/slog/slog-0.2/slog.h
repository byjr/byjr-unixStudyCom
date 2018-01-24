#ifndef _SLOG_H_
#define _SLOG_H_ 1

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>
#include <sys/time.h>

#define _STR(s)     #s 
#define STR(s)      _STR(s)
#define MAX_PNL 	64

#define Hgray   "\033[1;30m"
#define Lgray   "\033[0;30m"

#define Hred    "\033[1;31m"
#define Lred    "\033[0;31m"

#define Hgreen  "\033[1;32m"
#define Lgreen  "\033[0;32m"

#define Hyellow "\033[1;33m"
#define Lyellow "\033[0;33m"

#define Hblue 	"\033[1;34m"
#define Lblue 	"\033[0;34m"

#define Hpurple "\033[1;35m"
#define Lpurple "\033[0;35m"

#define Hindigo "\033[1;36m"
#define Lindigo "\033[0;36m"

#define Hwhite 	"\033[1;37m"
#define Lwhite 	"\033[0;37m"


#define TELNET_PATH	 "/dev/pts/0"
#define CONSOLE_PATH "/dev/console"
#define LOG_OUT_PATH ""

#define clog(color,fmt, args...) ({ \
    FILE *fp = fopen(LOG_OUT_PATH, "a"); \
	if(!fp)fp=stderr;\
	fprintf(fp,"%s[%s %d]:\033[0m",color,__FILE__,__LINE__); \
	fprintf(fp,fmt,##args); \
	fprintf(fp,"\n"); \
	if(fp!=stderr)fclose(fp); \
})

#define plog(path,fmt, args...) ({ \
    FILE *fp = fopen(path,"a"); \
    if (fp) { \
		fprintf(fp,"%s[%s %d]",__FILE__,__LINE__); \
        fprintf(fp,fmt,##args); \
		fprintf(fp,"\n"); \
        fclose(fp); \
    } \
})

typedef enum log_type_t{
	MIN_TYPE=-1,
	_RAW,	
	_ERR,
	_WAR,
	_INF,	
	_DBG,
	MAX_TYPE
}log_type_t;

typedef struct log_ctrl_t{
	char *name;
	char *color;
}log_ctrl_t;

extern void get_time_ms(char *ts,int size);
extern char log_ctrl_set[MAX_TYPE+1];
extern char out_path_set[MAX_PNL];
extern int log_init(char *ctl_str);
#define LOG_NOTE_PATH 	"/tmp/log_note.txt"
extern void slog(log_type_t num_type,char lock,char *log_ctrl_set,const char *out_file,const char *ts,
					const char *file,const int line,const char *fmt,...);
extern void raw_log(log_type_t n,char lock,char *log_ctrl_set,const char *out_path_set,const char *fmt,...);					
#define tlog(type,x...) ({\
	char ts[16]="";\
	get_time_ms(ts,sizeof(ts));\
	slog(type,log_ctrl_set,out_path_set,ts,__FILE__,__LINE__,x);\
})

#define dlog(type,lock,x...) slog(type,lock,log_ctrl_set,out_path_set,"",__FILE__,__LINE__,x);

#define rlog(type,lock,x...) raw_log(type,lock,log_ctrl_set,out_path_set,x);

#define raw(x...) 	rlog(_RAW,1,x);
#define err(x...) 	dlog(_ERR,1,x);
#define war(x...) 	dlog(_WAR,1,x);
#define inf(x...) 	dlog(_INF,1,x);
#define dbg(x...) 	dlog(_DBG,1,x);

#define raw_nl(x...) 	rlog(_RAW,0,x);
#define err_nl(x...) 	dlog(_ERR,0,x);
#define war_nl(x...) 	dlog(_WAR,0,x);
#define inf_nl(x...) 	dlog(_INF,0,x);
#define dbg_nl(x...) 	dlog(_DBG,0,x);

#define show_errno(ret, msg) ({\
	if(!ret)ret=errno;\
	err("%s failure,errno:%d[%s]",msg,ret,strerror(ret));\
})
#endif