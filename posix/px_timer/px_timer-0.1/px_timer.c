#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include "px_timer.h"

long get_tsd(struct timespec *pt1,struct timespec *pt2,char lev){
	long tsd=0;
	switch(lev){
	case 0://秒
		tsd=(pt2->tv_sec-pt1->tv_sec);
		break;
	case 1://毫秒
		tsd=(pt2->tv_sec*1000+pt2->tv_nsec/1000000)-(pt1->tv_sec*1000+pt1->tv_nsec/1000000);
		break;
	case 2://微妙
		tsd=(pt2->tv_sec*1000000+pt2->tv_nsec/1000)-(pt1->tv_sec*1000000+pt1->tv_nsec/1000);
		break;
	case 4://纳秒
		tsd=((pt2->tv_sec*1000000000+pt2->tv_nsec)-(pt1->tv_sec*1000000000+pt1->tv_nsec));
		break;
	default:
		return -1;
	}
	return tsd;
}