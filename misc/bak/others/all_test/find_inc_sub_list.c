#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#define ARG_NUM 1
#define log(x...) printf(x)
#define my_free(x){free(x);x=NULL;}
#define ARRAY_LEN (sizeof(a)/sizeof(a[0]))
//类型定义区
typedef  unsigned int uint;
//	全局变量定义区
int a[]={1,3,2,4,1,5,111,333,23,56,0,2,3,4,7,2,3,4,5,6,7};
int b[ARRAY_LEN],c[ARRAY_LEN];
uint cur_max_len=0;
void display(int c[],uint len){
	uint i=0;
	for(i=0;i<len;i++){
		log("%d\t",c[i]);	
	}
	log("\r\n");
}
uint get_a_increase_sub_list(uint a_i,uint b_i){
	uint i=0,t=1;
	b[b_i]=a[a_i];	
	for(i=a_i+1;i<ARRAY_LEN;i++){
		if(a[a_i]<a[i]){
			t=get_a_increase_sub_list(i,b_i+1);	
			//display(b,t+1);
			if(t>cur_max_len){		
				cur_max_len=t;
				memcpy(c,b,(t+1)*sizeof(c[0]));
			}				
		}		
	}
	return b_i;
}
int main(int argc,char* argv[]){
	uint cur_len=0,i=0;
	for(i=0;i<ARRAY_LEN;i++){
		cur_len=get_a_increase_sub_list(i,0);
		if(cur_len>cur_max_len){		
			cur_max_len=cur_len;
			memcpy(c,b,(cur_len+1)*sizeof(c[0]));
		}
	}
	log("the most len increase sub list is:\r\n");
	display(c,cur_max_len+1);
	return 0;
}