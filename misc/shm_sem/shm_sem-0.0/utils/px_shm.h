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
#include "lzl/px_sem.h"
int shm_open(const char *name, int oflag, mode_t mode);
int shm_unlink(const char *name);
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
int munmap(void *addr, size_t length);

typedef struct usr_shm_t{
	sem_t a2i_work_sem;
	int a2i_cmd;
	sem_t a2i_stop_sem;
}usr_shm_t;

void px_shm_get(void);
void shm_mem_init(void);
extern usr_shm_t *shm;
#define SHM_PATH "/sys_shm"

#define ch2i(x) ({\
	char ch=x;\
	(ch>='0'&&ch<='9')?(ch-'0')		:\
	(ch>='A'&&ch<='Z')?(ch-'A'+10)	:\
	(ch>='a'&&ch<='z')?(ch-'a'+10)	:\
	-1;\
})
#endif