#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MYSIG SIGRTMIN+1;

int main(int argc, char ** argv)
{
    pid_t pid=(pid_t)atoi(argv[1]);

    //发送的信号值
    int signo=MYSIG;

    //附带在信号上的参数
    union sigval mysigval;
    mysigval.sival_int=8;

    //发送信号
    if(sigqueue(pid, signo, mysigval)==-1)
    {
        printf("发送信号失败\n");
        return -1;
    }

    printf("成功发送信号\n");
    sleep(2);
}