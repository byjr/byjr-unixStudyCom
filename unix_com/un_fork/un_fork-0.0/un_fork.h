#ifndef UN_FORK_H_
#define UN_FORK_H_ 1
#define _GNU_SOURCE
#include <sched.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "lzl/misc.h"
#include "lzl/slog.h"

typedef int subFunc_t(void *);

#define M_BYTE (1024*1024)
pid_t my_clone(subFunc_t fn,void *args,int flag,size_t stack_size);
int vfexec_nowait(char *argl);
int vfexec(char *argl);
#endif