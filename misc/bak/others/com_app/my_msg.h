#ifndef _MSG_H_
#define _MSG_H_
#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/msg.h>  
#include <errno.h> 
#include <sys/types.h>
#include <sys/ipc.h>
typedef struct{
	int type;
	char txt[BUFSIZ];
}msg_t;
#endif