#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "un_select.h"
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/un_fop.h>
int fd=0;
char buf[BUF_SIZE]="";
int main(void)
{
	fd_set rfds,testfds;
	struct timeval tv;
	int ret;
	log_init(NULL);
	/* Watch stdin (fd 0) to see when it has input. */


	do{
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		ret = select(1, &rfds, NULL, NULL, NULL);
		if(-1==ret){
			show_errno(0,"select");
			continue;
		}
		if(!ret){
			war("select time out!")
			continue;
		}
        for(fd = 0; fd < FD_SETSIZE; ++fd){
            if(FD_ISSET(fd, &testfds)){
                if(fd == server_sockfd){//监听套接字可读表示，有新连接
                    client_len = sizeof(client_address);
                    client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);
                    FD_SET(client_sockfd, &readfds);//将客户端套接字放到可读集合中
                    printf("adding client on fd %d\n", client_sockfd);
                }else{
                    ioctl(fd, FIONREAD, &nread);

                    if(nread == 0){//读到0字节表示客户端断开socket
                        close(fd);
                        FD_CLR(fd, &readfds);//将套接字从集合中清除
                        printf("removing client on fd %d\n", fd);
                    }else{
                    
                        read(fd, &ch, 1);
                        sleep(5);
                        printf("serving cient on fd  %d\n", fd);
                        ch++;
                        write(fd, &ch, 1);
                    }

                }
            }
        }		
		memset(buf,0,sizeof(buf));
		un_read(fileno(stdin),buf,sizeof(buf));
		inf(buf);
	}while(1);
	exit(EXIT_SUCCESS);
}
