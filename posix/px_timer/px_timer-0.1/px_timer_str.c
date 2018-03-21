#include "px_timer.h"
int main(int argc,char **argv){
	char buf[]="Mar 19 15:43:27 CST 2018";
	char build[512]="";
	struct tm tm={0};
	strptime(buf, "%b %d %H:%M:%S CST %Y",&tm);
	bzero(build,sizeof(build)-1);
	strftime(build, sizeof(build)-1, "%Y%m%d%H%M%S", &tm); 
	war(build);
    return 0;
}	