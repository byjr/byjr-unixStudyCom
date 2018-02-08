#include "my_socket.c"

int main (int argc, char *argv[])
{
	int cfd=0;
	if(create_my_socket(&cfd)<0){
		return -1;
	}
	if(connect_un_server(cfd,UN_SOCKET_PATH)<0){
		return -1;
	}
	int i=0;char ch_send=0,ch_recv=0,bytes=0;	
	for (i = 0, ch_send = 'A'; i < 5; i++, ch_send++) {
		if ((bytes = write(cfd, &ch_send, 1)) == -1) { /*发消息给服务器*/
			err("");perror ("write");
			exit (EXIT_FAILURE);
		}
		sleep(1); /*休息二秒钟再发一次*/
		if ((bytes = read(cfd, &ch_recv, 1)) == -1) { /*接收消息*/
			err("");perror ("read");
			exit (EXIT_FAILURE);
		}
		inf ("receive from server data is %c", ch_recv);
	}
	close (cfd);
	return 0;
}

