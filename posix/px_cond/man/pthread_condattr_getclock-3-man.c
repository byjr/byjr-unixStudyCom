PTHREAD_CONDATTR_GETCLOCK(3POSIX)                                                                                                                                                      POSIX Programmer's Manual                                                                                                                                                     PTHREAD_CONDATTR_GETCLOCK(3POSIX)

PROLOG
       This manual page is part of the POSIX Programmer's Manual.  The Linux implementation of this interface may differ (consult the corresponding Linux manual page for details of Linux behavior), or the interface may not be implemented on Linux.

NAME
       pthread_condattr_getclock, pthread_condattr_setclock — get and set the clock selection condition variable attribute

SYNOPSIS
       #include <pthread.h>

       int pthread_condattr_getclock(const pthread_condattr_t *restrict attr,
           clockid_t *restrict clock_id);
       int pthread_condattr_setclock(pthread_condattr_t *attr,
           clockid_t clock_id);

DESCRIPTION
       The pthread_condattr_getclock() function shall obtain the value of the clock attribute from the attributes object referenced by attr.

       The pthread_condattr_setclock() function shall set the clock attribute in an initialized attributes object referenced by attr.  If pthread_condattr_setclock() is called with a clock_id argument that refers to a CPU-time clock, the call shall fail.

       The clock attribute is the clock ID of the clock that shall be used to measure the timeout service of pthread_cond_timedwait().  The default value of the clock attribute shall refer to the system clock.

       The behavior is undefined if the value specified by the attr argument to pthread_condattr_getclock() or pthread_condattr_setclock() does not refer to an initialized condition variable attributes object.

RETURN VALUE
       If successful, the pthread_condattr_getclock() function shall return zero and store the value of the clock attribute of attr into the object referenced by the clock_id argument. Otherwise, an error number shall be returned to indicate the error.

       If successful, the pthread_condattr_setclock() function shall return zero; otherwise, an error number shall be returned to indicate the error.

ERRORS
       The pthread_condattr_setclock() function may fail if:

       EINVAL The value specified by clock_id does not refer to a known clock, or is a CPU-time clock.

       These functions shall not return an error code of [EINTR].

       The following sections are informative.

EXAMPLES
       None.

APPLICATION USAGE
       None.

RATIONALE
       If an implementation detects that the value specified by the attr argument to pthread_condattr_getclock() or pthread_condattr_setclock() does not refer to an initialized condition variable attributes object, it is recommended that the function should fail and report an [EINVAL] error.

FUTURE DIRECTIONS
       None.

SEE ALSO
       pthread_cond_destroy(), pthread_cond_timedwait(), pthread_condattr_destroy(), pthread_condattr_getpshared(), pthread_create(), pthread_mutex_destroy()

       The Base Definitions volume of POSIX.1‐2008, <pthread.h>

COPYRIGHT
       Portions  of  this text are reprinted and reproduced in electronic form from IEEE Std 1003.1, 2013 Edition, Standard for Information Technology -- Portable Operating System Interface (POSIX), The Open Group Base Specifications Issue 7, Copyright (C) 2013 by the Institute of Electrical and Electronics Engineers, Inc and The Open Group.  (This is POSIX.1-2008 with the 2013 Technical
       Corrigendum 1 applied.) In the event of any discrepancy between this version and the original IEEE and The Open Group Standard, the original IEEE and The Open Group Standard is the referee document. The original Standard can be obtained online at http://www.unix.org/online.html .

       Any typographical or formatting errors that appear in this page are most likely to have been introduced during the conversion of the source files to man page format. To report such errors, see https://www.kernel.org/doc/man-pages/reporting_bugs.html .

IEEE/The Open Group                                                                                                                                                                              2013                                                                                                                                                                PTHREAD_CONDATTR_GETCLOCK(3POSIX)
