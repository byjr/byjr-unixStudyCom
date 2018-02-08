#include "my_socket.c"
int un_srv_proc(int cfd){
	inf ("The server is waiting for client data...");
	int i=0;char ch_send=0,ch_recv=0,bytes=0;
	for (i = 0, ch_send = '1'; i < 5; i++, ch_send++) {
		if ((bytes = read (cfd, &ch_recv, 1)) == -1) {
			perror ("read");
			exit (EXIT_FAILURE);
		}
		inf ("The character receiver from client is %c", ch_recv);
		sleep (1);
		if ((bytes = write (cfd, &ch_send, 1)) == -1) {
			err("");perror ("read");
			return -1;
		}
	}
	close(cfd);	
	return 0;
}
int main (int argc, char *argv[])
{
	int sfd=0;
	if(create_my_socket(&sfd)<0){
		return -1;
	}
	if(bind_my_socket(sfd,UN_SOCKET_PATH)<0){
		return -1;
	}
	if(listen_socket(sfd,5)<0){
		return -1;
	}
	int cfd=0;
	while(1){
		if(accept_client(&cfd,sfd)<0){
			return -1;
		}
		
	}


	return 0;	
}