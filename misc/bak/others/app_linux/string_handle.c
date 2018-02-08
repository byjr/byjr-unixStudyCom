#include "log.h"
	char str[]="012345abcdefghi";
//	char str[]="012d45abc0efghi";	
//	char str[]="abcdefghi012345";
int swp_sub_string(char *a,uint len,uint pos){
	char t1,t2;
	t1=a[len-pos-1];
	a[len-pos-1]=a[0];
	
	t1=a[len-1];
	a[len-1]=a[pos];
	t2=a[len-pos-1];
	a[len-pos-1]=t1;
	a[pos]=t2;
	return 0;
};
typedef struct A_T{
	int xxx;
	char yyy[4];
	char zzz[0];
}a_t;
int main(int argc,char **argv){
	//swp_sub_string(str,sizeof(str),5);
	
	log("char----%d\r\n",(int)sizeof(char));
	log("uchar----%d\r\n",(int)sizeof(unsigned char));
	log("short----%d\r\n",(int)sizeof(short));
	log("short int----%d\r\n",(int)sizeof(short int));	
	log("ushort----%d\r\n",(int)sizeof(unsigned short));
	log("int ----%d\r\n",(int)sizeof(int));
	log("uint----%d\r\n",(int)sizeof(unsigned int));
	log("long----%d\r\n",(int)sizeof(long));	
	log("long int----%d\r\n",(int)sizeof(long int));		
	log("ull----%d\r\n",(int)sizeof(unsigned long long));
	//log("----%d\r\n",(int)sizeof(long long long));		
	return 0;
}