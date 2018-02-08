#ifndef UN_SELECT_H_
#define UN_SELECT_H_
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

//____________________________________________________________________________
/* void FD_CLR(int fd, fd_set *set);
int  FD_ISSET(int fd, fd_set *set);
void FD_SET(int fd, fd_set *set);
void FD_ZERO(fd_set *set);
int select(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds,\
			struct timeval *timeout);
int pselect(int nfds, fd_set *readfds, fd_set *writefds,fd_set *exceptfds,\
			const struct timespec *timeout,	const sigset_t *sigmask); */
//____________________________________________________________________________//

//_____________________________________________________________________________
#define BUF_SIZE 1024

//_____________________________________________________________________________//



#endif