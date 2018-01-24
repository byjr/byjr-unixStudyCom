#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>
#include "pthread.h"
#include "slog.h"
// \033[显示方式;前景色;背景色m
/* 	显示方式:0（默认值）、1（高亮）、22（非粗体）、4（下划线）、24（非下划线）、5（闪烁）、25（非闪烁）、7（反显）、27（非反显）
	前景色:30（黑色）、31（红色）、32（绿色）、 33（黄色）、34（蓝色）、35（洋红）、36（青色）、37（白色）
	背景色:40（黑色）、41（红色）、42（绿色）、 43（黄色）、44（蓝色）、45（洋红）、46（青色）、47（白色） */
//注：如果增减了以下项，注意在log.h中增减对应的枚举值
	
log_ctrl_t log_ctrl_array[MAX_TYPE]={
	[_ERR]	={"ERR"		,"\033[1;31m"},
	[_WAR]	={"WAR"		,"\033[1;33m"},
	[_DBG]	={"DBG"		,"\033[1;34m"},
	[_INF]	={"INF"		,"\033[1;32m"},
};
char log_ctrl_set[MAX_TYPE+1]="11100";
char out_path_set[MAX_PNL]="";

void get_time_ms(char *ts,int size){
	struct timeval tv={0};
	if(gettimeofday(&tv,NULL)<0){
		return;
	}
	snprintf(ts,size,"%013lu",tv.tv_sec*1000+tv.tv_usec/1000); 
}

int log_init(char *cfg_str){
	int ret=0;
	if(!cfg_str)return 0;
	char *idx=strstr(cfg_str,"l=");
	if(idx)sscanf(idx,"l=%"STR(MAX_TYPE)"s",log_ctrl_set);
	idx=strstr(cfg_str,"op=");
	if(idx)sscanf(idx,"op=%"STR(MAX_PNL)"s",out_path_set);
	return 0;
}
pthread_mutex_t line_lock = PTHREAD_MUTEX_INITIALIZER;
void slog(log_type_t n,char *log_ctrl_set,const char *out_path_set,const char *ts,\
					const char *file,const int line,const char *fmt,...){
	pthread_mutex_lock(&line_lock);
	if('1'==log_ctrl_set[n]){
		FILE *fp=NULL;
		if(out_path_set[0]){
			if(!(fp=fopen(out_path_set,"a"))){
				printf("fopen %s fail,errno=%d\n",out_path_set,errno);
				fp=stderr;
			}
		}else{
			fp=stderr;
		}
		va_list args;
		fprintf(fp,"[%s%s%s\033[0m %s %d]:",ts,log_ctrl_array[n].color,log_ctrl_array[n].name,file,line);			
		va_start(args,fmt);
		vfprintf(fp,fmt,args);
		va_end(args);
		fprintf(fp,"\n");		
		if(fp!=stderr){
			if(fclose(fp)){
				printf("error:close %s fail,errno=%d\n",out_path_set,errno);
			}
		}
	}
	pthread_mutex_unlock(&line_lock);
}
void raw_log(log_type_t n,char *log_ctrl_set,const char *out_path_set,const char *fmt,...){
	pthread_mutex_lock(&line_lock);
	if('1'==log_ctrl_set[n]){
		FILE *fp=NULL;
		if(out_path_set[0]){
			if(!(fp=fopen(out_path_set,"a"))){
				printf("fopen %s fail,errno=%d\n",out_path_set,errno);
				fp=stderr;
			}
		}else{
			fp=stderr;
		}
		va_list args;
		va_start(args,fmt);
		vfprintf(fp,fmt,args);
		va_end(args);
		if(fp!=stderr){
			if(fclose(fp)){
				printf("error:close %s fail,errno=%d\n",out_path_set,errno);
			}
		}
	}
	pthread_mutex_unlock(&line_lock);
}