#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>
#include "sv_sem.h"
#include "slog.h"
// \033[显示方式;前景色;背景色m
/* 	显示方式:0（默认值）、1（高亮）、22（非粗体）、4（下划线）、24（非下划线）、5（闪烁）、25（非闪烁）、7（反显）、27（非反显）
	前景色:30（黑色）、31（红色）、32（绿色）、 33（黄色）、34（蓝色）、35（洋红）、36（青色）、37（白色）
	背景色:40（黑色）、41（红色）、42（绿色）、 43（黄色）、44（蓝色）、45（洋红）、46（青色）、47（白色） */
//注：如果增减了以下项，注意在log.h中增减对应的枚举值	
log_ctrl_t log_ctrl_array[MAX_LOG_TYPE_T]={
	[_ERR]	={"ERR"		,"\033[1;31m"},
	[_WAR]	={"WAR"		,"\033[1;33m"},
	[_DBG]	={"DBG"		,"\033[1;34m"},
	[_INF]	={"INF"		,"\033[1;32m"},
};
char log_ctrl_set[MAX_LOG_TYPE_T+1]="1111";
void get_local_time_str(char *ts,int size){
	time_t t = time(NULL);
	struct tm *lt = localtime(&t);
	strftime(ts,size,"%H:%M:%S",lt);
}
void get_time_ms(char *ts,int size){
	struct timeval tv={0};
	if(gettimeofday(&tv,NULL)<0){
		return;
	}
	snprintf(ts,size,"%013lu",tv.tv_sec*1000+tv.tv_usec/1000); 
}
static int semid=0;
int log_init(char *ctl_str){
	int ret=0;
	sv_semget(&semid,1,SLOG_SEM_SIPC);
	sv_semset(semid,0,+1);
	if(NULL==ctl_str){
		return 0;
	}
	ret=sscanf(ctl_str,"l=%04s",log_ctrl_set);
	if(ret!=1){
		return -1;
	}
	return 0;
}
void slog(log_type_t num_type,char *log_ctrl_set,const char *out_file,const char *ts,const char *file,const int line,const char *fmt,...){
	int ret=0;
	sv_semop(semid,0,-1);
	if('1'==log_ctrl_set[num_type]){
		FILE *fp=NULL;
		if(out_file){
			if(!(fp=fopen(out_file,"a"))){
				printf("fopen %s fail,errno=%d\n",out_file,errno);
				fp=stderr;
			}
		}else{
			fp=stderr;
		}
		va_list args;
		fprintf(fp,"[%s%s%s\033[0m %s %d]:",ts,log_ctrl_array[num_type].color,log_ctrl_array[num_type].name,file,line);			
		va_start(args,fmt);
		vfprintf(fp,fmt,args);
		va_end(args);
		fprintf(fp,"\n");		
		if(fp!=stderr){
			if(fclose(fp)){
				printf("error:close %s fail,errno=%d\n",out_file,errno);
			}
		}
	}
	sv_semset(semid,0,+1);
}
#if 0
int main(int argc,char ** argv){
	do{	
		char ts[16]="";		
		get_local_time_str(ts,sizeof(ts));
		if(update_log_set_from_file(LOG_SET_PATH)<0){
			printf("error:%s line:%d:update_log_set_from_file %s fial!\n",__FILE__,__LINE__,LOG_SET_PATH);
		}
		err("好哈哈哈哈哈");
		usleep(3000);
		war("操蛋");
		usleep(5000);
		inf("你是谁");
		usleep(8000);
		dbg("%s",__func__);
		usleep(9000);
	}while(1);
	return 0;
}
#endif