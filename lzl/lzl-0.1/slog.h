#ifndef MY_LOG_H_
#define MY_LOG_H_
#define SLOG_SEM_SIPC 1

#define _STR(s)     #s 
#define STR(s)      _STR(s)
#define MAX_PNL 128

typedef enum log_type_t{
	MIN_TYPE=-1,
	_RAW,	
	_ERR,
	_WAR,
	_DBG,
	_INF,
	MAX_TYPE
}log_type_t;

typedef struct log_ctrl_t{
	char *name;
	char *color;
}log_ctrl_t;

extern void get_time_ms(char *ts,int size);
extern char log_ctrl_set[MAX_TYPE+1];
char out_path_set[MAX_PNL];
extern int log_init(char *ctl_str);
#define LOG_NOTE_PATH 	"/tmp/log_note.txt"
extern void slog(log_type_t num_type,char *log_ctrl_set,const char *out_file,const char *ts,
					const char *file,const int line,const char *fmt,...);
extern void raw_log(log_type_t n,char *log_ctrl_set,const char *out_path_set,const char *fmt,...);					
#define tlog(type,x...) ({\
	char ts[16]="";\
	get_time_ms(ts,sizeof(ts));\
	slog(type,log_ctrl_set,out_path_set,ts,__FILE__,__LINE__,x);\
})

#define dlog(type,x...) slog(type,log_ctrl_set,out_path_set,"",__FILE__,__LINE__,x);

#define rlog(type,x...) raw_log(type,log_ctrl_set,out_path_set,x);

#define raw(x...) 	rlog(_RAW,x);
#define err(x...) 	dlog(_ERR,x);
#define war(x...) 	dlog(_WAR,x);
#define dbg(x...) 	dlog(_DBG,x);
#define inf(x...) 	dlog(_INF,x);

#endif