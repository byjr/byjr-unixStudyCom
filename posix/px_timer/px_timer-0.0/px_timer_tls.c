#include <stdlib.h>
#include <lzl/slog.h>
#include <lzl/misc.h>
#include <time.h>

int main(int argc,char **argv){
	int ret=0;
	clockid_t cid=0;
	timer_t tm_id=0;
	time_t tt1={0},tt2={0},tt3={0};
	struct tm *p_tm=NULL;
	struct timespec tvs={0,10000000},tvs1={0};
	double tv=0;
	log_init(NULL);
	inf("sizeof(clock_t)=%d",sizeof(clock_t));
	inf("sizeof(time_t)=%d",sizeof(time_t));
	inf("sizeof(size_t)=%d",sizeof(size_t));
	time(&tt1);
	inf("time=%ld",time(NULL));
	// ret=clock_getres(CLOCK_REALTIME,&tvs1);
	// ret=clock_getres(CLOCK_MONOTONIC ,&tvs1);
	// ret=clock_getres(CLOCK_PROCESS_CPUTIME_ID  ,&tvs1);
	// ret=clock_getres(CLOCK_THREAD_CPUTIME_ID,&tvs1);//?没有变化

	// inf("clock_getres:%09ld",tvs1.tv_nsec);
	do{
		// time(&tt2);
		// tv=difftime(tt2,tt1);
		// inf("tt2=%d",tt2);
		// inf("tv=%lf",tv);
		// p_tm=localtime(&tt2);
		// tt3=mktime(p_tm);
		// inf("tt3=%d",tt3);
		ret=clock_gettime(CLOCK_REALTIME,&tvs1);
		if(ret){
			show_errno(0,"clock_gettime");
		}
		inf("clock_gettime:%09ld",tvs1.tv_nsec);
		nanosleep(&tvs,NULL);
	}while(1);
	return 0;
}