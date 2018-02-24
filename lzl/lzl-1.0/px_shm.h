#ifndef PX_SHM_
#define PX_SHM_ 1
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <time.h>
#include "slog.h"
#include "misc.h"

int shm_open(const char *name, int oflag, mode_t mode);
int shm_unlink(const char *name);
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
int munmap(void *addr, size_t length);

typedef struct usr_shm_t{
	int fd;
	int sv[2];
	pthread_mutex_t mtx;
	pthread_spinlock_t spLock;
	pthread_cond_t cond;
	char cmd_buf[64];
	char dat_buf[1024];
}usr_shm_t;
int px_shm_get(usr_shm_t **p_ptr,const char *name);
#endif