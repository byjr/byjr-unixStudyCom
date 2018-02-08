#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#define MYSIG SIGRTMIN+1;

//声明信号响应函数
void new_act(int, siginfo_t *, void *);

int main()
{
    //指明对信号响应的设置信息
    struct sigaction myAct;
    //标识指明，信号响应函数可以使用传输过来的参数
    myAct.sa_flags=SA_SIGINFO;
    //指明信号响应函数
    myAct.sa_sigaction=new_act;

    int signo=MYSIG;
    //安装信号，为MYSIG设置响应函数
    if(sigaction(signo, &myAct, NULL)<0)
    {
        printf("安装信号失败\n");
    }

    while(1)
    {
        sleep(2);
        printf("一直循环，直到信号的到来\n");
    }
}

//信号响应函数
void new_act(int signum, siginfo_t * info, void * myact)
{
    printf("接收到信号，信号值为%d\n", signum);
    printf("int参数为%d\n", info->si_value.sival_ptr);
}