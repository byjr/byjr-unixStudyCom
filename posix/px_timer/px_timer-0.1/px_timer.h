#ifndef _UN_RWLOCK_H
#define _UN_RWLOCK_H 1
#define __USE_GNU 1
#if 0

extern clock_t clock(void);//进程启动到当前调用处的节拍数 failure return -1;
extern time_t time(time_t *__timer);//unix纪元当前调用处的时间(秒) failure return -1;
extern double difftime(time_t __time1,time_t __time0);间隔
extern time_t mktime(struct tm *__tp);//tm -> time_t
extern size_t strftime(char * __s,size_t __maxsize,const char * __format,const struct tm * __tp);//
extern char *strptime(const char * __s,const char * __fmt,struct tm *__tp);
extern size_t strftime_l(char * __s,size_t __maxsize,const char * __format,const struct tm * __tp,__locale_t __loc);
extern char *strptime_l(const char * __s,const char * __fmt,struct tm *__tp,__locale_t __loc);
extern struct tm *gmtime(const time_t *__timer); //time_t -> GMT
extern struct tm *localtime(const time_t *__timer); 
extern struct tm *gmtime_r(const time_t * __timer,struct tm * __tp);
extern struct tm *localtime_r(const time_t * __timer,struct tm * __tp);
extern char *asctime(const struct tm *__tp);
extern char *ctime(const time_t *__timer);
extern char *asctime_r(const struct tm * __tp,char * __buf);
extern char *ctime_r(const time_t * __timer,char * __buf);
extern int stime(const time_t *__when);
extern time_t timegm(struct tm *__tp);
extern time_t timelocal(struct tm *__tp);
extern int dysize(int __year);//返回某年有多少天
extern int nanosleep(const struct timespec *__requested_time,struct timespec *__remaining);
extern int clock_getres(clockid_t __clock_id,struct timespec *__res);//没有验证到效果
extern int clock_gettime(clockid_t __clock_id,struct timespec *__tp);
extern int clock_settime(clockid_t __clock_id,const struct timespec *__tp);
extern int clock_nanosleep(clockid_t __clock_id,int __flags,const struct timespec *__req,struct timespec *__rem);//flag:0,相对(调用处)时间；1，绝对时间
extern int clock_getcpuclockid(pid_t __pid,clockid_t *__clock_id);
extern int timer_create(clockid_t __clock_id,struct sigevent * __evp,timer_t * __timerid);

extern int timer_delete(timer_t __timerid);
extern int timer_settime(timer_t __timerid,int __flags,const struct itimerspec * __value,struct itimerspec *__ovalue);
extern int timer_gettime(timer_t __timerid,struct itimerspec *__value);//获取剩余时间（减计数器）
extern int timer_getoverrun(timer_t __timerid); //取得一个定时器的超限运行次数(信号丢失次数)
extern int timespec_get(struct timespec *__ts,int __base);
extern struct tm *getdate(const char *__string);
extern int getdate_r(const char * __string,struct tm * __resbufp);
//以下接口用于select/epoll场景
extern int timerfd_gettime (int __ufd, struct itimerspec *__otmr);
extern int timerfd_settime (int __ufd, int __flags,const struct itimerspec *__utmr,struct itimerspec *__otmr);
extern int timerfd_create (clockid_t __clock_id, int __flags);

extern int settimeofday(const struct timeval *__tv, const struct timezone *__tz);
extern int adjtime(const struct timeval *__delta,struct timeval *__olddelta);
extern int getitimer(__itimer_which_t __which,struct itimerval *__value);
extern int setitimer(__itimer_which_t __which,const struct itimerval * __new,struct itimerval * __old);
extern int utimes(const char *__file, const struct timeval __tvp[2]);
extern int lutimes(const char *__file, const struc t timeval __tvp[2]);
extern int futimes(int __fd, const struct timeval __tvp[2]);
extern int futimesat(int __fd, const char *__file,const struct timeval __tvp[2]);

1.tmID 不能在进程间共享（即使tmID 定义在 共享内存区也不行）
2.it_interval：倒计时周期；it_value：倒计时起点
3.如何获取 单调时间、原始单调时间等：clock_gettime，使用下面的clockid:
	CLOCK_REALTIME,
	CLOCK_MONOTONIC,
	CLOCK_PROCESS_CPUTIME_ID,
	CLOCK_THREAD_CPUTIME_ID,
	CLOCK_MONOTONIC_RAW,
	CLOCK_REALTIME_COARSE,
	CLOCK_MONOTONIC_COARSE,
	CLOCK_BOOTTIME,
	CLOCK_REALTIME_ALARM,
	CLOCK_BOOTTIME_ALARM,
	// CLOCK_SGI_CYCLE,
	CLOCK_TAI,	
#endif
int mt_start(clockid_t cid);
long long mt_get(clockid_t cid);

#define px_gettime(cid,pts) ({\
	int ret=clock_gettime(cid,pts);\
	if(ret<0)show_errno(0,"px_gettime");\
	ret?-1:0;\
})
#define px_settime(cid,pts) ({\
	int ret=clock_settime(cid,pts);\
	if(ret<0)show_errno(0,"px_gettime");\
	ret?-1:0;\
})
long get_tsd(struct timespec *pt1,struct timespec *pt2,char lev);
#define get_tsv(tv,t2,t1) ({\
	int ret=-1;\
	(tv).tv_sec=(t2).tv_sec-(t1).tv_sec;\
	(tv).tv_nsec=(t2).tv_nsec-(t1).tv_nsec;\
	if((tv).tv_nsec<0){\
		(tv).tv_sec--;\
		(tv).tv_nsec=1000000000-(t1).tv_nsec+(t2).tv_nsec;\
	}\
	(tv).tv_nsec<0?-1:0;\
})

#define px_timer_create(cid,p_evp,p_id)({\
	int ret=0;\
	ret=timer_create(cid,p_evp,p_id);\
	if(-1==ret)	show_errno(0,"px_timer_create");\
	ret?-1:0;\
})

#define px_timer_set(id,flag,p_v,p_ov)({\
	int ret=0;\
	ret=timer_settime(id,flag,p_v,p_ov);\
	if(-1==ret)	show_errno(0,"px_timer_set");\
	ret?-1:0;\
})
#define px_timer_get(id,p_v)({\
	int ret=0;\
	ret=timer_gettime(id,p_v);\
	if(-1==ret)	show_errno(0,"px_timer_get");\
	ret?-1:0;\
})
#define px_timer_del(id)({\
	int ret=0;\
	ret=timer_delete(id);\
	if(-1==ret)	show_errno(0,"px_timer_del");\
	ret?-1:0;\
})
#define px_timer_getoverrun(id)({\
	int ret=0;\
	ret=timer_getoverrun(id);\
	if(-1==ret)	show_errno(0,"px_timer_getoverrun");\
	ret;\
})
#endif