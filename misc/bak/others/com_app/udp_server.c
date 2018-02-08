#include "log.h"
#include "udp_com.h"
#define NUM_ARG 1
#define debug(x...) log("server:");log(x);
int main(int argc,char *argv[])
{
	int server_fd;
	struct sockaddr_in server_addr;
	if(argc!=NUM_ARG){
		debug("NUM_ARG is not %d!\r\n",NUM_ARG);
		return -1;
	}
	
	server_fd=socket(AF_INET,SOCK_DGRAM,0);
	if(server_fd<0){
		debug("creat socket fail\r\n");
		return -1;
	}
		
	bzero(&server_addr,sizeof(struct sockaddr_in));
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	server_addr.sin_port=htons(SERVER_PORT);
    int ret = bind(server_fd, (struct sockaddr*)&server_addr, sizeof(struct sockaddr));
    if(ret < 0){
        debug("socket bind fail!\n");
        return -1;
    }
		
	for(;;){
		char send_buff[LEN_UDP_GRAM_BUF]="";
		char recive_buff[2*LEN_UDP_GRAM_BUF]="";
		struct sockaddr_in client_addr;
		socklen_t len;
		int recive_count=0,send_count=0;
		bzero(&client_addr,sizeof(struct sockaddr_in));
		do{
			debug("recive msg %d times!\r\n",++recive_count);
			ret=recvfrom(server_fd,recive_buff,sizeof(recive_buff),0,\
				(struct sockaddr*)&client_addr,&len);	
			sleep(1);
		}while(ret<0);

		if(!strncmp(recive_buff,"end",3)){
			return 0;
		}
		debug("recive msg:%s\r\n",recive_buff);
		
		sprintf(send_buff,"please input some date:\r\n");
		do{			
			debug("send msg %d times!\r\n",++send_count);
			ret=sendto(server_fd,send_buff,strlen(send_buff),0,\
				(struct sockaddr*)&client_addr,sizeof(struct sockaddr));
			sleep(1);
		}while(ret<0);		
		debug("send msg %d:%s\r\n",ret,send_buff);
	}
}