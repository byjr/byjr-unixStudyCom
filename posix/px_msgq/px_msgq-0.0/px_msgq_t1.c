#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <mqueue.h>
int main(int argc, char **argv)
{       
	int flags = 0;
	mqd_t mqd;
	flags = O_RDWR | O_CREAT;
	char *mq_name = (char*)"/MQ_Msg";
	struct mq_attr attr;
	long int msgsize = 1024;
	long int maxmsg = 5;
	attr.mq_msgsize = msgsize;
	attr.mq_maxmsg = maxmsg;
	mqd = mq_open(mq_name, flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH, &attr);
	if (mqd == -1){
		printf("mq create error %d[%s]\n",errno,strerror(errno));
		return 0;
	}
	printf("Create MQ success!\nMax msgs = %ld, Max bytes/msg = %ld\n",  attr.mq_maxmsg, attr.mq_msgsize);
	char msg[1024] = "hello";
	unsigned int prio = 1;
	int i;
	for (i = 0;	i < 100;i++){
		mq_send(mqd, msg, msgsize, prio);
	}
	mq_close(mqd);
	return 0;
}
