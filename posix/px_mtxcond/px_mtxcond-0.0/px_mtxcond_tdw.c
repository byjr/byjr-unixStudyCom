#include <stdio.h>
#include <pthread.h>
#include <time.h>
typedef struct st2_t{
	char str_ar[10];
	char *str;	
}st2_t;
typedef struct st1_t{
	char str_ar[10];
	char *str;
	st2_t st2;
	int a;
}st1_t;

// g++ -o pwait pwait.cpp -lpthread -lrt
st1_t st1={"111","222",{"333","444"}};
int main(){
	st1_t *p_st1=&st1;
	printf("%s\n",p_st1->str_ar);
	printf("%x\n",p_st1->a);
	printf("%x\n",(&st1)->a);
	return 0;
}
