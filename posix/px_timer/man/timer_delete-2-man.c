TIMER_DELETE(2)                                        Linux Programmer's Manual                                       TIMER_DELETE(2)

NAME
       timer_delete - delete a POSIX per-process timer

SYNOPSIS
       #include <time.h>

       int timer_delete(timer_t timerid);

       Link with -lrt.

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       timer_delete(): _POSIX_C_SOURCE >= 199309L

DESCRIPTION
       timer_delete() deletes the timer whose ID is given in timerid.  If the timer was armed at the time of this call, it is disarmed
       before being deleted.  The treatment of any pending signal generated by the deleted timer is unspecified.

RETURN VALUE
       On success, timer_delete() returns 0.  On failure, -1 is returned, and errno is set to indicate the error.

ERRORS
       EINVAL timerid is not a valid timer ID.

VERSIONS
       This system call is available since Linux 2.6.

CONFORMING TO
       POSIX.1-2001, POSIX.1-2008.

SEE ALSO
       clock_gettime(2), timer_create(2), timer_getoverrun(2), timer_settime(2), time(7)

COLOPHON
       This page is part of release 4.09 of the Linux man-pages project.  A description of the project,  information  about  reporting
       bugs, and the latest version of this page, can be found at https://www.kernel.org/doc/man-pages/.

Linux                                                         2015-08-08                                               TIMER_DELETE(2)
