#ifndef PX_SHM_
#define PX_SHM_ 1
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <time.h>
#include "lzl/slog.h"
#include "lzl/misc.h"

int shm_open(const char *name, int oflag, mode_t mode);
int shm_unlink(const char *name);
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
int munmap(void *addr, size_t length);

int px_shm_get(void **p_ptr,const char *name);

#ifndef PX_SHM_INIT_SIZE
#define PX_SHM_INIT_SIZE 100
#endif

#endif