#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "un_flock.c"
int main(int argc,char **argv)
{
    FILE *fp = NULL;
    int ret=0,fail=1;;    
    if ((fp = fopen(TEST_FILE_PATH, "a+")) == NULL){
        show_error(fp,"fopen");
		goto Exit0;
	}inf(TEST_FILE_PATH);
	ret=flock(fp->_fileno,LOCK_EX);
	if(ret<0){
		show_error(ret,"fwrite");
		goto Exit1;
	}
	int i=({int i=atoi(argv[1]);i>0&&i<100?i:0;});
    while(i){   
        inf("%d", i--);
        sleep(1);
		int len=strlen(argv[2]);		
		ret=fwrite(argv[2],sizeof(char),len,fp);
		if(ret<len){
			show_error(ret,"fwrite");
			err("len=%d",len);
			goto Exit1;
		}	
    }  
	ret=flock(fp->_fileno, LOCK_UN);
	if(ret<0){
		show_error(ret,"LOCK_UN");
		goto Exit1;
	}
	fail=0;
Exit1:	
    fclose(fp);
Exit0:		
	if(fail)return -1;
    return 0;
}