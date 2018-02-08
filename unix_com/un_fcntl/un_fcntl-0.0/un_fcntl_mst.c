#include <stdio.h>
#include <malloc.h>
#define sizeMalloc(p) (*(((unsigned int *) p) - 1) & (0x01|0x02))
int get_malloc_size(void *p){
	if(!p)	return -1;
	unsigned int *p_a=(unsigned int *)p - sizeof(int);
	return *p_a;
}
size_t malloc_usable_size (void *ptr);
int main(void)
{
   int i=0;
	do{
	   for(i=0; i<50; i++) {
		   char *pa= (char *)malloc(i);
		   size_t size=malloc_usable_size(pa);
		   printf("i=%04d,malloc_usable_size=%04d\n",i,(int)size);
		   pa[size-1]=1;
		   free(pa);
	   }		
	}while(1);
   return 0;
}