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
#include "lzl/slog.h"

typedef int subFunc_t(void *);

#define M_BYTE (1024*1024)

#endif