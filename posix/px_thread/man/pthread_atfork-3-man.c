PTHREAD_ATFORK(3)                                                                                                                                                                      Library Functions Manual                                                                                                                                                                      PTHREAD_ATFORK(3)

NAME
       pthread_atfork - register handlers to be called at fork(2) time

SYNOPSIS
       #include <pthread.h>

       int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));

DESCRIPTION
       pthread_atfork  registers  handler  functions  to  be called just before and just after a new process is created with fork(2). The prepare handler will be called from the parent process, just before the new process is created. The parent handler will be called from the parent process, just before fork(2) returns. The child handler will be called from the child process, just before
       fork(2) returns.

       One or several of the three handlers prepare, parent and child can be given as NULL, meaning that no handler needs to be called at the corresponding point.

       pthread_atfork can be called several times to install several sets of handlers. At fork(2) time, the prepare handlers are called in LIFO order (last added with pthread_atfork, first called before fork), while the parent and child handlers are called in FIFO order (first added, first called).

       To understand the purpose of pthread_atfork, recall that fork(2) duplicates the whole memory space, including mutexes in their current locking state, but only the calling thread: other threads are not running in the child process.  The mutexes are not usable after the fork and must be initialized with pthread_mutex_init in the child process.  This is a limitation  of  the  current
       implementation and might or might not be present in future versions.

RETURN VALUE
       pthread_atfork returns 0 on success and a non-zero error code on error.

ERRORS
       ENOMEM insufficient memory available to register the handlers.

AUTHOR
       Xavier Leroy <Xavier.Leroy@inria.fr>

SEE ALSO
       fork(2), pthread_mutex_lock(3), pthread_mutex_unlock(3).

                                                                                                                                                                                             LinuxThreads                                                                                                                                                                            PTHREAD_ATFORK(3)
