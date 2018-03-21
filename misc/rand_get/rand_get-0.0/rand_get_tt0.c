#include "rand_get.c"

#include "lzl/misc.h"

typedef unsigned int uint32_t;

#define RED_WANT 	6

#define BLUE_WANT 	1

#define ALL_WANT 	RED_WANT+BLUE_WANT

#define RED_TOTAL 	33
#define BLUE_TOTAL 	16

void buble_sort(uint32_t a[],size_t size){
	int i=0,j=0,t=0;
    for(i=0;i<size-1;i++){  
        for(j=0;j<size-i-1;j++){  
            if(a[j]>a[j+1]){  
               t=a[j+1];  
               a[j+1]=a[j];  
               a[j]=t; 
            }  
        }  
    } 	
}
int get_reds(uint32_t blue){
	// srand(time(NULL));
	uint32_t tbl[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,0};
	uint32_t remain=RED_TOTAL;
	uint32_t red_want=RED_WANT;
	uint32_t ary[RED_WANT]={0};
	uint32_t i=0;
	do{uint32_t idx=rand()%remain;
		ary[red_want]=tbl[idx];
		for(i=idx;tbl[i+1];i++){
			tbl[i]=tbl[i+1];
		}
		tbl[i]=0;
		remain--;	
	}while(red_want--);
	buble_sort(ary,getCount(ary));
	for(i=0;i<getCount(ary);i++){
		raw("%02d,",ary[i]);
	}
	raw(" %02d\n",blue);
}

int main(int argc,char *argv[]){
	log_init("l=11111");
	assert(argv[1]);
	assert(argv[2]);
	int count=atoi(argv[1]);		
	srand(atoi(argv[2]));
	int i=0;
	for(i=0;i<count;i++){
		uint32_t blue=count==16?(i%16)+1:rand()%16+1;
		get_reds(blue);
	}
}