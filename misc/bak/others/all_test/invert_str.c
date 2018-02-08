#include <stdio.h>
#include <string.h>
#define log(x...) //printf(x)
#define MIN(a,b) ((a.len)<(b.len)?(a):(b))
#define MAX(a,b) ((a.len)>(b.len)?(a):(b))
typedef struct{
	char * st;
	unsigned int len;
}sub_s_t;
char a[]="abcdefg()123456789011111111112222222222233333333377777777777777777777777";
#define SPLITE 7


sub_s_t s;
sub_s_t swap_sub_str(sub_s_t s1,sub_s_t s2){	
	unsigned int i=0;
	log("s1:%d,%d\ts2:%d,%d\r\n",s1.st-a,s1.len,s2.st-a,s2.len);
	for(i=0;i<MIN(s1,s2).len;i++){
		char t=s1.st[i];
		s1.st[i]=s2.st[i];
		s2.st[i]=t;
	}
	log("---%s\n",a);
	return MAX(s1,s2);
}
void invert(sub_s_t s1,sub_s_t s2){
	while(1){
		sub_s_t ts=swap_sub_str(s1,s2);
		if(ts.st==s1.st){
			s1.st+=MIN(s1,s2).len;	
			s1.len-=MIN(s1,s2).len;
			s2.st=s1.st+s1.len;
		}else{
			s1.st+=MIN(s1,s2).len;
			s1.len=MIN(s1,s2).len;
			s2.st=s1.st+MIN(s1,s2).len;
			s2.len=s2.len-MIN(s1,s2).len;
		}
		if(!s2.len)
			return;				
	}
}
int main(int argc,char* argv[])
{	
	sub_s_t s1,s2;
	s1.st=a;
	s1.len=SPLITE;
	s2.st=a+SPLITE;
	s2.len=strlen(s2.st);
	printf("%s\n",a);
	invert(s1,s2);
	printf("%s\n",a);
	return 0;
}