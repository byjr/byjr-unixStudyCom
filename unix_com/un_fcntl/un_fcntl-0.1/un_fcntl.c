#include "un_fcntl.h"
int fdSetNonBlock(int fd){
	int ret=fcntl(fd,F_GETFL,0);
	if(ret<0)return -1;
	ret=fcntl(fd,F_SETFL,ret|O_NONBLOCK);
	if(ret<0)return -1;
	return 0;
}

	
		
