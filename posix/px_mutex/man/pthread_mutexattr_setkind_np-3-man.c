PTHREAD_MUTEXATTR_SETKIND_NP(3)                        Library Functions Manual                        PTHREAD_MUTEXATTR_SETKIND_NP(3)

NAME
       pthread_mutexattr_setkind_np, pthread_mutexattr_getkind_np - deprecated mutex creation attributes

SYNOPSIS
       #include <pthread.h>

       int pthread_mutexattr_setkind_np(pthread_mutexattr_t *attr, int kind);

       int pthread_mutexattr_getkind_np(const pthread_mutexattr_t *attr, int *kind);

DESCRIPTION
       These functions are deprecated, use pthread_mutexattr_settype(3) and pthread_mutexattr_gettype(3) instead.

RETURN VALUE
       pthread_mutexattr_getkind_np always returns 0.

       pthread_mutexattr_setkind_np returns 0 on success and a non-zero error code on error.

ERRORS
       On error, pthread_mutexattr_setkind_np returns the following error code:

       EINVAL kind is neither PTHREAD_MUTEX_FAST_NP nor PTHREAD_MUTEX_RECURSIVE_NP nor PTHREAD_MUTEX_ERRORCHECK_NP

AUTHOR
       Xavier Leroy <Xavier.Leroy@inria.fr>

SEE ALSO
       pthread_mutexattr_settype(3), pthread_mutexattr_gettype(3).

                                                             LinuxThreads                              PTHREAD_MUTEXATTR_SETKIND_NP(3)
