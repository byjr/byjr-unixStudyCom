#ifndef LOG_H_
#define LOG_H_
	#include <stdio.h>
	#include <string.h>	
	#include <stdlib.h>	
	#define LOG_EN 1
	#if LOG_EN
		#define log(fmt,args...) printf(fmt,##args)
	#else
		#define log(fmt,args...)
	#endif
	typedef unsigned int uint;
	typedef unsigned char uchar;
	typedef unsigned short ushort;
#endif