#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "fp_op.c"

int main(void)
{
	FILE* stream;
	_G_va_list __arg;
	char buf[1024]="";
	char *string="Thisisatest";
	fpos_t filepos;
	/*openafileforupdate*/
	#define FILE_PATH "DUMMY.FIL"
	stream=fopen(FILE_PATH,"r+");
	/*writeastringintothefile*/
	fwrite(string,strlen(string),3,stream);
	/*reportthefilepointerposition*/
	fgetpos(stream,&filepos);
	fclose(stream);
	char *str=NULL;
	int ret=fp_read_str(&str,FILE_PATH);
	if(ret)return -1;
	pause();
	return 0;
}