#include "px_timer.h"

long get_tsd(struct timespec *pt2,struct timespec *pt1,char lev){	
	struct timespec tv={0};
	long tsd=get_tsv(tv,*pt2,*pt1);
	if(tsd<0)return -1;
	inf("tv=%3d.%09d",tv.tv_sec,tv.tv_nsec);
	switch(lev){
	case 's'://秒
		tsd=tv.tv_sec;
		break;
	case 'm'://毫秒
		tsd=tv.tv_sec*1000+tv.tv_nsec/1000000;
		break;
	case 'u'://微秒
		tsd=tv.tv_sec*1000000+tv.tv_nsec/1000;
		break;
	case 'n'://纳秒
		tsd=tv.tv_sec*1000000000+tv.tv_nsec;
		break;
	default:
		return -1;
	}
	return tsd;
}

static struct timespec mts;
int mt_start(clockid_t cid){
	int ret=px_gettime(cid,&mts);
	if(ret<0)return -1;
	return 0;
}

long long mt_get(clockid_t cid){
	struct timespec ts,tv;
	int ret=px_gettime(cid,&ts);
	if(ret<0)return -1;	
	ret= get_tsv(tv,ts,mts);
	if(ret<0)return -1;	
	return tv.tv_sec*1000000000+tv.tv_nsec;
}

char *get_fmt_time(char *tm_str,size_t size,char *fmt){
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	strftime(tm_str,size,fmt,timeinfo);
	return tm_str;
}