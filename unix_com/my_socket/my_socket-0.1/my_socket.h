#ifndef UN_SOCKET_H_
#define UN_SOCKET_H_
#define __USE_GNU  1
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
//____________________________________________________________________________
int socket(int domain, int type, int protocol);
int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
int listen(int sockfd, int backlog);
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int accept4(int sockfd, struct sockaddr *addr,socklen_t *addrlen, int flags);

//____________________________________________________________________________//

//_____________________________________________________________________________


//_____________________________________________________________________________//
#define UN_SOCK_PATH "/tmp/un_sock.t"
#define BUF_LENTH 1024
int create_my_socket(int *p_fd);
int bind_my_socket(int fd,char *path);
int listen_socket(int fd,int maximum);
int accept_client(int *p_cfd,int sfd);
int accept_client_no_wait(int *p_cfd,int sfd);
int connect_un_server(int fd,char *path);
#endif