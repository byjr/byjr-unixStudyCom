#ifndef UN_SOCKET_H_
#define UN_SOCKET_H_
#define __USE_GNU  1

int create_my_socket(int *p_fd);
int bind_my_socket(int fd,char *path);
int listen_socket(int fd,int maximum);
int accept_client(int *p_cfd,int sfd);
int accept_client_no_wait(int *p_cfd,int sfd);
int connect_un_server(int fd,char *path);
#define UN_SOCKET_PATH "/tmp/server_socket"
#endif