#include <signal.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <time.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include "px_timer.h"

long get_tsd(struct timespec *pt1,struct timespec *pt2,char lev){
	switch(lev){
	case 0://秒
		return (pt2->tv_sec-pt1->tv_sec);
	case 1://毫秒
		return (pt2->tv_sec-pt1->tv_sec)*1000+(pt2->tv_nsec-pt1->tv_nsec)/1000000;
	case 2://微妙
		return (pt2->tv_sec-pt1->tv_sec)*1000000+(pt2->tv_nsec-pt1->tv_nsec)/1000;
	case 4://纳秒
		return (pt2->tv_nsec-pt1->tv_nsec);
	default:
		return 0;
	}
}