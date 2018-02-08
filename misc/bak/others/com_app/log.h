#ifndef _LOG_H
#define _LOG_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
#define LOG_ON 1
	#if LOG_ON
		#define log(fmt,args...) printf(fmt,##args)
	#else 
		#define log(fmt,args...)
	#endif
#endif