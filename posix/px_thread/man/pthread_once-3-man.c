PTHREAD_ONCE(3)                                                                                                                                                                        Library Functions Manual                                                                                                                                                                        PTHREAD_ONCE(3)

NAME
       pthread_once - once-only initialization

SYNOPSIS
       #include <pthread.h>

       pthread_once_t once_control = PTHREAD_ONCE_INIT;

       int pthread_once(pthread_once_t *once_control, void (*init_routine) (void));

DESCRIPTION
       The purpose of pthread_once is to ensure that a piece of initialization code is executed at most once. The once_control argument points to a static or extern variable statically initialized to PTHREAD_ONCE_INIT.

       The first time pthread_once is called with a given once_control argument, it calls init_routine with no argument and changes the value of the once_control variable to record that initialization has been performed. Subsequent calls to pthread_once with the same once_control argument do nothing.

RETURN VALUE
       pthread_once always returns 0.

ERRORS
       None.

AUTHOR
       Xavier Leroy <Xavier.Leroy@inria.fr>

                                                                                                                                                                                             LinuxThreads                                                                                                                                                                              PTHREAD_ONCE(3)
