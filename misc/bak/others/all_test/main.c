#include <stdio.h>
#define ARG_NUM 1
#define log(x...) printf(x)
#pragma pack(4)
typedef struct TEST_T{
	int a:3;
	int b:5;
	int c;
	int d:3;
	int e;
	int f:5;
}test_t;
int main(int argc,char* argv[]){
	int i=0;
	int a=3,b=5,c,d;
	if(ARG_NUM!=argc){
		log("please input arg:%d\r\n",ARG_NUM);
	}
/* 	for(i=0;i<argc;i++){
		log("--%d:%s\r\n",i,argv[i]);
	}
	log("-->func:%s,line:%d\r\n",__func__,__LINE__); */
	log("---:%d,%d\r\n",(int)sizeof(test_t),d);
	return 0;
}