#include <stdio.h>
#define ARG_NUM 1
#define log(fmt,args...) printf(fmt,##args)
int main(int argc,char* argv[]){
	int i=0;
	if(ARG_NUM!=argc){
		log("please input arg:%d\r\n",ARG_NUM);
	}
	for(i=1;i<argc;i++){
		log("--%d:%s\r\n",i,argv[i]);
	}
	log("-->func:%s,line:%d\r\n",__func__,__LINE__);
	return 0;
}