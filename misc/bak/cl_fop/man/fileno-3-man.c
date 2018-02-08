FERROR(3)                                                                                                       Linux Programmer's Manual                                                                                                      FERROR(3)

NAME
       clearerr, feof, ferror, fileno - check and reset stream status

SYNOPSIS
       #include <stdio.h>

       void clearerr(FILE *stream);

       int feof(FILE *stream);

       int ferror(FILE *stream);

       int fileno(FILE *stream);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       fileno(): _POSIX_C_SOURCE

DESCRIPTION
       The function clearerr() clears the end-of-file and error indicators for the stream pointed to by stream.

       The function feof() tests the end-of-file indicator for the stream pointed to by stream, returning nonzero if it is set.  The end-of-file indicator can be cleared only by the function clearerr().

       The function ferror() tests the error indicator for the stream pointed to by stream, returning nonzero if it is set.  The error indicator can be reset only by the clearerr() function.

       The function fileno() examines the argument stream and returns its integer file descriptor.

       For nonlocking counterparts, see unlocked_stdio(3).

ERRORS
       These functions should not fail and do not set the external variable errno.  (However, in case fileno() detects that its argument is not a valid stream, it must return -1 and set errno to EBADF.)

ATTRIBUTES
       For an explanation of the terms used in this section, see attributes(7).

       ┌────────────────────┬───────────────┬─────────┐
       │Interface           │ Attribute     │ Value   │
       ├────────────────────┼───────────────┼─────────┤
       │clearerr(), feof(), │ Thread safety │ MT-Safe │
       │ferror(), fileno()  │               │         │
       └────────────────────┴───────────────┴─────────┘
CONFORMING TO
       The functions clearerr(), feof(), and ferror() conform to C89, C99, POSIX.1-2001, and POSIX.1-2008.

       The function fileno() conforms to POSIX.1-2001 and POSIX.1-2008.

SEE ALSO
       open(2), fdopen(3), stdio(3), unlocked_stdio(3)

COLOPHON
       This page is part of release 4.09 of the Linux man-pages project.  A description of the project, information about reporting bugs, and the latest version of this page, can be found at https://www.kernel.org/doc/man-pages/.

                                                                                                                       2016-03-15                                                                                                              FERROR(3)