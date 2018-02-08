#define __USE_GNU 1
#include <string.h>
#include <stdio.h>
#include <lzl/slog.h>
int strchr_t(){
	char *str="01234567890123456789";
	char *idx=NULL;
	idx=strchr(str,'8');
	inf("%d",idx-str);
	return 0;
}
int strrchr_t(){
	char *str="01234567890123456789";
	char *idx=NULL;
	idx=strrchr(str,'8');
	inf("%d",idx-str);
	return 0;
}
// int strchrnul_t(){
	// char *str="01234567890123456789";
	// char *idx=NULL;
	// idx=strchrnul(str,'a');
	// inf("0x%08x",idx);
	// inf("%d",idx-str);
	// return 0;
// }
int main(void)
{
	log_init(NULL);
	
	// strchrnul_t();
	// strrchr_t();
	// strchr_t();
	while(1);
	return 0;
}