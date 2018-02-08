#include "log.h"
int src_array[100]={33,1,2,9,3,4,1,3,5,3,4,5,6,7,8, 10,0,14};
 uint max_len=0;
void func(int * a,uint star,uint n,uint len,int**ta_p,int**tta_p){
	uint i=star;
	(*ta_p)[len]=a[star];
	for(;i<n;i++){
			log("\r\n-------------------------\r\n");
		if((*tta_p)[len]<=a[i]){
			func(a,i,n,len+1,ta_p,tta_p);
		}
	}
	if(max_len<len){
		max_len=len;
		memcpy((*ta_p),(*tta_p),n*sizeof(int));
	}
}
void find_the_longest_ascending_subsequence(int a[],uint n)
{
	uint i;
	int *ta=(int*)calloc(n,sizeof(int));
	if(NULL==ta)
		printf("calloc mem fail!\r\n");
	int *tta=(int*)calloc(n,sizeof(int));
	if(NULL==tta)
		printf("calloc mem fail!\r\n");		
	func(a,0,n,0,&ta,&tta);
	for(i=0;i<=max_len;i++){
		log("%d\t",ta[i]);
	}
	log("\r\n-------------------------\r\n");
}
int main(int argc,char**argv){
	find_the_longest_ascending_subsequence(src_array,sizeof(src_array)/sizeof(src_array[0]));
	return 0;
}
