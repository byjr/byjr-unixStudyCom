#include "un_fifo.c"
#include <stdlib.h>
#include <signal.h>
char cmd_buf[FIFO_BUF_SIZE]="";
int main(int argc,char **argv)
{
	log_init("l=11111");
	un_fifo_init("+");
	do{
		inf(argv[1]);
		un_fifo_write("1111111111\n",6);
	}while(0);
}