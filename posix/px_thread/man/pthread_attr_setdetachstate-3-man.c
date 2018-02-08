PTHREAD_ATTR_SETDETACHSTATE(3)                                                                                                                                                         Linux Programmer's Manual                                                                                                                                                        PTHREAD_ATTR_SETDETACHSTATE(3)

NAME
       pthread_attr_setdetachstate, pthread_attr_getdetachstate - set/get detach state attribute in thread attributes object

SYNOPSIS
       #include <pthread.h>

       int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
       int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);

       Compile and link with -pthread.

DESCRIPTION
       The pthread_attr_setdetachstate() function sets the detach state attribute of the thread attributes object referred to by attr to the value specified in detachstate.  The detach state attribute determines whether a thread created using the thread attributes object attr will be created in a joinable or a detached state.

       The following values may be specified in detachstate:

       PTHREAD_CREATE_DETACHED
              Threads that are created using attr will be created in a detached state.

       PTHREAD_CREATE_JOINABLE
              Threads that are created using attr will be created in a joinable state.

       The default setting of the detach state attribute in a newly initialized thread attributes object is PTHREAD_CREATE_JOINABLE.

       The pthread_attr_getdetachstate() returns the detach state attribute of the thread attributes object attr in the buffer pointed to by detachstate.

RETURN VALUE
       On success, these functions return 0; on error, they return a nonzero error number.

ERRORS
       pthread_attr_setdetachstate() can fail with the following error:

       EINVAL An invalid value was specified in detachstate.

ATTRIBUTES
       For an explanation of the terms used in this section, see attributes(7).

       ┌───────────────────────────────┬───────────────┬─────────┐
       │Interface                      │ Attribute     │ Value   │
       ├───────────────────────────────┼───────────────┼─────────┤
       │pthread_attr_setdetachstate(), │ Thread safety │ MT-Safe │
       │pthread_attr_getdetachstate()  │               │         │
       └───────────────────────────────┴───────────────┴─────────┘
CONFORMING TO
       POSIX.1-2001, POSIX.1-2008.

NOTES
       See pthread_create(3) for more details on detached and joinable threads.

       A thread that is created in a joinable state should eventually either be joined using pthread_join(3) or detached using pthread_detach(3); see pthread_create(3).

       It is an error to specify the thread ID of a thread that was created in a detached state in a later call to pthread_detach(3) or pthread_join(3).

EXAMPLE
       See pthread_attr_init(3).

SEE ALSO
       pthread_attr_init(3), pthread_create(3), pthread_detach(3), pthread_join(3), pthreads(7)

COLOPHON
       This page is part of release 4.09 of the Linux man-pages project.  A description of the project, information about reporting bugs, and the latest version of this page, can be found at https://www.kernel.org/doc/man-pages/.

Linux                                                                                                                                                                                         2015-08-08                                                                                                                                                                PTHREAD_ATTR_SETDETACHSTATE(3)
