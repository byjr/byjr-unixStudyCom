#include "log.h"
#include "udp_com.h"
#define NUM_ARG 2
#define debug(x...) log("client:");log(x);	
int main(int argc,char *argv[])
{
	int client_fd,ret;
	struct sockaddr_in server_addr;
	if(argc!=NUM_ARG){
		debug("NUM_ARG is not %d!\r\n",NUM_ARG);
		return -1;
	}
	
	client_fd=socket(AF_INET,SOCK_DGRAM,0);
	if(client_fd<0){
		debug("creat socket fail\r\n");
		return -1;
	}
		
	bzero(&server_addr,sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	//server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);	
	server_addr.sin_port=htons(SERVER_PORT);
	
	for(;;){
		char send_buff[LEN_UDP_GRAM_BUF]="";
		char recive_buff[2*LEN_UDP_GRAM_BUF]="";
		struct sockaddr_in client_addr;
		int send_count=0,recive_count=0;
		socklen_t len;
		scanf("%s",send_buff);
		if(!strncmp(send_buff,"end",3)){
			return 0;
		}
		do{
			debug("send msg %d times!\r\n",++send_count);
			ret=sendto(client_fd,send_buff,strlen(send_buff),0,\
				(struct sockaddr*)&server_addr,sizeof(struct sockaddr));	
			sleep(1);
		}while(ret<0);
		debug("send msg %d:%s\r\n",ret,send_buff);
		do{
			debug("recive msg %d times!\r\n",++recive_count);
			ret=recvfrom(client_fd,recive_buff,sizeof(recive_buff),0,\
				(struct sockaddr*)&client_addr,&len);
			sleep(1);
		}while(ret<0);		
		debug("recive msg:%s\r\n",recive_buff);		
	}	
}