#include <pthread.h>
#include "px_mutex.c"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutexattr_t mattr={0};
int main(int argc,char *argv[])
{
	pthread_mutexattr_init(&mattr);
	pthread_mutex_init(&mutex,&mattr);
	px_get_attr(&mattr);
	return 0;
}