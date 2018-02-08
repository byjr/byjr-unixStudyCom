#include <string.h>
// #define __USE_GNU 1
#include <stdio.h>
#include <unistd.h>
#include "fp_op.c"




#define ALIVE_CODE_SEG 11
int main(void){
	log_init(NULL);
#if ALIVE_CODE_SEG == 0
#elif ALIVE_CODE_SEG == 11
	#define BUF_SIZE 5
	char *membuf=(char*)calloc(1,BUF_SIZE);
	if(!membuf){
		err("");
		return -1;
	}
	size_t mb_size=BUF_SIZE;
	#define MB_INIT_STRING "666666"
	strncpy(membuf,MB_INIT_STRING,BUF_SIZE);
	
	char buf[BUF_SIZE]="";	
	FILE *fp=fmemopen(&membuf,BUF_SIZE,"r+");
	if(fp<0){
		show_errno(0,fp);
		return -1;
	}
	size_t ret_size=0;
	
	ret_size=fp_read(buf,sizeof(char),sizeof(buf),fp);
	if(ret_size<0)return -1;
	inf("ret_size=%d,buf:%s",ret_size,buf);	
	
	#define WSTRING "888888"
	ret_size=fp_write(WSTRING,sizeof(char),strlen(WSTRING),fp);
	if(ret_size<0)return -1;
	inf(membuf);
	
	memset(buf,0,sizeof(buf));
	ret_size=fp_read(buf,sizeof(char),sizeof(buf),fp);
	if(ret_size<0)return -1;
	inf("ret_size=%d,buf:%s",ret_size,buf);
	// FREE(membuf);
	inf(membuf);
	fp_close(fp);
	inf(membuf);
	return 0;
#elif ALIVE_CODE_SEG == 9
	char *ret_str=NULL;
	ret_str=tmpnam("123");
	if(!ret_str)show_errno(0,"tmpnam");
	inf(ret_str);
#elif ALIVE_CODE_SEG == 8
---------------
	#define BUF_SIZE 5
	// #define GETDELIM_PATH "/home/lz/work/w-rt-study/misc/fp_op/getdelim_file"
	// FILE* fp=fp_open(GETDELIM_PATH,"r");
	// if(!fp)return -1;
	
	size_t max_line_lenth=BUF_SIZE;
	char *line=(char*)calloc(1,max_line_lenth);
	if(!line)return -1;
	char *ret_str=NULL;
	ret_str=gets(line,BUF_SIZE);
	if(!ret_str){
		// show_errno(0,"fgets");
		err("");
		return -1;
	}
	inf(ret_str);
	inf(line);
	inf("0x%08x,0x%08x",line,ret_str);
	return 0;
#elif ALIVE_CODE_SEG == 7
	#define BUF_SIZE 1024
	#define GETDELIM_PATH "/home/lz/work/w-rt-study/misc/fp_op/getdelim_file"
	FILE* fp=fp_open(GETDELIM_PATH,"r");
	if(!fp)return -1;
	
	size_t max_line_lenth=BUF_SIZE;
	char *line=(char*)calloc(1,max_line_lenth);
	if(!line)return -1;
	char *ret_str=NULL;
	ret_str=fgets(line,BUF_SIZE,fp);
	if(!ret_str){
		// show_errno(0,"fgets");
		err("");
		return -1;
	}
	inf(ret_str);
	inf(line);
	inf("0x%08x,0x%08x",line,ret_str);
	return 0;
#elif ALIVE_CODE_SEG == 6
	#define BUF_SIZE 1024
	char buf[BUF_SIZE]="";
	inf(ctermid(NULL));
	inf(ctermid(buf));
	inf(buf);
#elif ALIVE_CODE_SEG == 5
---------------
	#define BUF_SIZE 1024
	char buf[BUF_SIZE]="";
	inf(cuserid(NULL));
	inf(cuserid(buf));
	inf(buf);
#elif ALIVE_CODE_SEG == 4
	#define BUF_SIZE 1024
	#define GETDELIM_PATH "/home/lz/work/w-rt-study/misc/fp_op/getdelim_file"
	FILE* fp=fp_open(GETDELIM_PATH,"r");
	if(!fp)return -1;
	
	size_t max_line_lenth=BUF_SIZE;
	char *line=(char*)calloc(1,max_line_lenth);
	if(!line)return -1;
	size_t ret_size=0;
	do{
		ret_size=getdelim(&line,&max_line_lenth,'#',fp);
		if((int)ret_size<=0){
			err("getdelim");
			return -1;
		}
		inf("ret_size=%d,line:%s",ret_size,line);
	}while(ret_size>0);

	return 0;
#elif ALIVE_CODE_SEG == 3
	#define BUF_SIZE 1024
	#define GETLINE_PATH "/home/lz/work/w-rt-study/misc/fp_op/getline_file"
	FILE* fp=fp_open(GETLINE_PATH,"r");
	if(!fp)return -1;
	
	size_t max_line_lenth=BUF_SIZE;
	char *line=(char*)calloc(1,max_line_lenth);
	if(!line)return -1;
	size_t ret_size=0;
	do{
		ret_size=getline(&line,&max_line_lenth,fp);
		if((int)ret_size<=0){
			err("getline");
			return -1;
		}
		inf("ret_size=%d,line:%s",ret_size,line);
	}while(ret_size>0);

	return 0;
#elif ALIVE_CODE_SEG == 2
	#define BUF_SIZE 5
	char *membuf=(char*)calloc(1,BUF_SIZE);
	if(!membuf){
		err("");
		return -1;
	}
	size_t mb_size=BUF_SIZE;
	#define MB_INIT_STRING "666666"
	strncpy(membuf,MB_INIT_STRING,BUF_SIZE);
	
	char buf[BUF_SIZE]="";	
	FILE *fp=open_memstream(&membuf,&mb_size);
	if(fp<0){
		show_errno(0,fp);
		return -1;
	}
	size_t ret_size=0;
	
	ret_size=fp_read(buf,sizeof(char),sizeof(buf),fp);
	if(ret_size<0)return -1;
	inf("ret_size=%d,buf:%s",ret_size,buf);	
	
	#define WSTRING "888888"
	ret_size=fp_write(WSTRING,sizeof(char),strlen(WSTRING),fp);
	if(ret_size<0)return -1;
	inf(membuf);
	
	memset(buf,0,sizeof(buf));
	ret_size=fp_read(buf,sizeof(char),sizeof(buf),fp);
	if(ret_size<0)return -1;
	inf("ret_size=%d,buf:%s",ret_size,buf);
	// FREE(membuf);
	inf(membuf);
	fp_close(fp);
	inf(membuf);
	return 0;
#elif ALIVE_CODE_SEG ==1
	FILE* stream;
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
#endif	
	do{
		pause();
	}while(1);	
	return 0;
}