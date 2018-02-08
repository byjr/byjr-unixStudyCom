#include "my_socket.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <lzl/px_thread.h>
#include <lzl/misc.h>
#include <lzl/slog.h>
#include <lzl/un_fop.h>

int main (int argc, char *argv[])
{
	struct sockaddr_in addr={AF_INET};
	addr.sin_port=htons(5188);
	addr.sin_addr.s_addr=inet_addr("127.0.0.1");	
	return 0;
}