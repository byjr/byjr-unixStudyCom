#include <unistd.h>
#include <lzl/slog.h>
#include <lzl/misc.h>
#include <lzl/un_fop.h>
#include "un_fcntl.h"
int main(int argc,char *argv[]){
	int ret=0;
	char *content=NULL;
	do{
		char buf[1024]="";
		int ret=read_fstring(&content,TEST_FILE_PATH);
		if(ret<0)continue;
		inf(content);
		exec_cmd3(buf,sizeof(buf),"cat %s",TEST_FILE_PATH);
		inf(buf);
		FREE(content);
		sleep(1);
	}while(1);
	return 0;
}