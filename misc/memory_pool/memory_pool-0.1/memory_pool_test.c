#include <stdio.h>
#include "memory_pool.h"
#define LOOP 5
#define ALLOC_SIZE 8
int main(void){
    Memory_Pool *pool = NULL;
    char *p1 = NULL;
    char *p2 = NULL;
    int i = 0;
    pool = memory_pool_create(1024,512);
    if (pool == NULL) printf("memory pool init failed\n");
    for (i = 0; i < 2; i++){
        p1 = (char *)Memory_malloc(pool,ALLOC_SIZE);
        if (p1 == NULL) printf("Malloc failed\n");
        else printf("Malloc success\n");
        memory_free(pool,p1);
    }
    p1 = (char *)Memory_malloc(pool,256);
    if (p1 == NULL)printf("Malloc failed\n");
    else printf("Malloc success\n");
	
    p2 = (char *)Memory_malloc(pool,512);
    if (p1 == NULL) printf("Malloc failed\n");
    else printf("Malloc success\n");	
    memory_free(pool,p1);
	
    p1 = (char *)Memory_malloc(pool,256);
    if (p1 == NULL) printf("Malloc failed\n");
    else printf("Malloc success\n");
    memory_pool_destroy(pool);
	
    return 0;
}