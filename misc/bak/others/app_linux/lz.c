#include "stdio.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define log printf
#define ARG_NUM 3
#define MAX_NUM 1000
typedef unsigned int uint;
void show_array
void buble_sort(int a[],uint n){
	int i,j;
	for(i=1;i<n;i++){
		for(j=0;j<n-i;j++){
			if(a[j]>a[j+1]){
				int tmp=a[j];
				a[j]=a[j+1];
				a[j+1]=tmp;
			}
		}
		{
			int i;
			for(i=0;i<n;i++){
				log("%d\t",a[i]);
			}
			log("\r\n");			
		}
	}

}
int check_end(){
	typedef union {
		short m;
		char n;
	}aa_t;
	aa_t aaa={
		0x1234
	};
	if(aaa.n==0x12){
		return 1;
	}
	return 0;
}
char * loop_move(char *str,unsigned int step){
	unsigned int size=strlen(str);
	unsigned int mov_size=step%size;
	char *buf_p=(char *)calloc(1,size+1);
	strncpy(buf_p,str+(size-mov_size),mov_size);
	strncpy(buf_p+mov_size,str,size-mov_size);
	memset(str,0,size);
	strncpy(str,buf_p,size);
	free(buf_p);
	return str;
}
#define xxx 5
int main(int argc,char* argv[]){
#if xxx==0
#elif xxx==5
	int a[]={1,2,4,9,8,11,13,22,8,4,3,3,5,7,6,0};
	buble_sort(a,sizeof(a)/sizeof(a[0]));
#elif xxx==4
	printf("---%d\r\n",check_end());
#elif xxx==3
unsigned int step;
if(argc!=ARG_NUM){
	log("the arg num isn't %d\r\n",ARG_NUM);
	return -1;
}
step=atoi(argv[2]);
log("-----%d,%s\r\n",step,loop_move(argv[1],step));
#elif xxx==2
	typedef struct {
		long bzy:1;
		long wrt:1;
		long rd:1;
		long cnt:4;
		long rsd:25;
	}RegX;
	printf("---%d\r\n",sizeof(RegX));
#elif xxx==1	
	int i=0,count=0;
	if(argc!=ARG_NUM){
		log("ERR:para number is not %d!\r\n",ARG_NUM);
		return -1;
	}
	count=atoi(argv[1]);
	for(;i<count;i++){
		sleep(1);
		log("--------%d:%s\r\n",i,argv[2]);
	}
	return 0;
#endif	
};