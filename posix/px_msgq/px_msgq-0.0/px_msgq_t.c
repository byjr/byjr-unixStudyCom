#include "px_msgq.c"
#include <unistd.h>
#define TTT_PX_MSGQ "/ttt1"
int main(int argc,char **argv)
{
	mqd_t t_mq={0};
	struct mq_attr attr={0};
	px_msgq_open(&t_mq,TTT_PX_MSGQ);
	while(1){
		px_msgq_getattr(&attr,t_mq);
		px_msgq_showattr(&attr);
		sleep(1);
	}
	return 0;
}



