/* CELEBP64 */                                   
/* Example using SUSv3 pthread_attr_getstackaddr() interface */ 

#define _UNIX03_THREADS 1

#include <stdio.h>                                                              
#include <stdlib.h>
#include <pthread.h>                                                            
#include <limits.h>                                                            
#include <errno.h>                                                            
                                                                                
int main(void)
{
   pthread_attr_t attr;                                                         
   int              rc; 
   void  *stackaddr;
   void  *mystack;
                                                                                
   if (pthread_attr_init(&attr) == -1) {                                        
      perror("error in pthread_attr_init");                                     
      exit(1);                                                                  
   }                                                                            

   /* Get a big enough stack and align it on 4K boundary. */
   mystack = malloc(PTHREAD_STACK_MIN * 2);
   if (mystack != NULL) {
      printf("Using PTHREAD_STACK_MIN to align stackaddr %x.\n", mystack);
      mystack = (void *)((((long)mystack + (PTHREAD_STACK_MIN - 1)) /
                          PTHREAD_STACK_MIN) * PTHREAD_STACK_MIN);
   } else {
      perror("Unable to acquire storage.");
      exit(2);
   }
                                                                                
   printf("Setting stackaddr to %x\n", mystack);
   rc = pthread_attr_setstackaddr(&attr, mystack);
   if (rc != 0) {                                           
      printf("pthread_attr_setstackaddr returned: %d\n", rc); 
      printf("Error: %d, Errno_Jr: %08x\n", errno, __errno2());
      exit(3);                                                                  
   } else {
      printf("Set stackaddr to %x\n", mystack);
   }

   rc = pthread_attr_getstackaddr(&attr, &stackaddr);
   if (rc != 0) {                                           
      printf("pthread_attr_getstackaddr returned: %d\n", rc); 
      printf("Error: %d, Errno_Jr: %08x\n", errno, __errno2());
      exit(4);                                                                  
   } else {
      printf("Retrieved stackaddr is %x\n", stackaddr);
   }

   rc = pthread_attr_destroy(&attr);
   if (rc != 0) {                                     
      perror("error in pthread_attr_destroy");                                  
      printf("Returned: %d, Error: %d\n", rc, errno); 
      printf("Errno_Jr: %x\n", __errno2());
      exit(5);                                                                  
   }                                                                            

   exit(0);                                                                     
}                    