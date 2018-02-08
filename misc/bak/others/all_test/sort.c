#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
//宏定义区
#define ARG_NUM 1
#define log(x...) printf(x)
//#define log(fmt,args...) printf(fmt,##args)
#define my_free(x){free(x);x=NULL;}
#define ARRAY_LEN(a) (sizeof(a)/sizeof(a[0]))
//类型定义区
typedef  unsigned int uint;
//全局变量定义区
int a[]={3,4,2,9,0,1,6,7,8,5,444,0,4,5};

//函数方法实现区
void display(int c[],uint len)
{
	uint i=0;
	for(i=0;i<len;i++){
		log("%d\t",c[i]);	
	}
	log("\r\n");
}
void swap(int* a,int* b){ 
	int t=0;
	t=*a;
	*a=*b;
	*b=t;
}
int bubble_sort(int a[],uint n){
	uint i=0;	
	if(!a)	
		return -1;
	for(i=0;i<n-1;i++){
		uint j=0;
		for(j=0;j<n-1-i;j++){
			if(a[j]>a[j+1]){
				int t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}
		}
		display(a,n);
	}	
	return 0;
}
int select_sort(int a[],uint n){
	int i=0;	
	if(!a)
		return -1;
	for(i=0;i<n-1;i++){
		uint j=i+1,k=i;
		for(;j<n;j++){
			if(a[j]<a[k]){
				k=j;
			}			
		}
		log("k=%d,a[k]=%d\t:",k,a[k]);		
		swap(&a[k],&a[i]);
		display(a,n);		
	}
	return 0;
}
int shell_sort(int a[],uint n){
	
	return 0;	
}
int insert_sort(int a[],uint n){
	
	return 0;
}
int quick_sort(int a[],uint n){
	uint left=0,right=n-2,pivot=n-1;
	if(!a)	
		return -1;
	if(n<=2)
		return 0;		
	if(n==2){
		if(a[0]>a[1])
			swap(a,a+1);
		return 1;
	}
	for(;left<right;){
		for(;left<right;left++)
			if(a[left]>a[pivot])
				break;
		for(;left<right;right--)
			if(a[right]<a[pivot])
				break;
		if(left<right)
			swap(a+left,a+right);				
	}
	if(a[left]>a[pivot])
		swap(a+left,a+pivot);
	quick_sort(a,left);	
	quick_sort(a+left,n-left);
	return 2;
}
int main(int argc,char* argv[])
{
	uint n=ARRAY_LEN(a);
	display(a,n);	
	if(quick_sort(a,n)<0)
		log("sort fail\r\n");
	display(a,n);
	return 0;
}