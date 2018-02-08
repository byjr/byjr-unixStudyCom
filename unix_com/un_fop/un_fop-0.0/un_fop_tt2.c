#include <stdio.h>
 #include <string.h>

#define MAX_TYPE 4
#define MAX_PNL 128

#define _STR(x)     #x 
#define STR(x)      _STR(x)

#define L_SCAN 	"%*[^l]l=%"STR(MAX_TYPE)"s"
#define OP_SCAN "op=%"STR(MAX_PNL)"s"
#define SCAN_ALL ""
#define T_STRING	"op=/tmp/xxx.c l=123"
int main(int argc, char *argv[]){
	int ret=0;
	char out_path_set[MAX_PNL+1]="";
	char log_ctrl_set[MAX_TYPE+1]="";
	
	printf("OP_SCAN=%s\n",OP_SCAN);
	printf("L_SCAN=%s\n",L_SCAN);
	sscanf(T_STRING,OP_SCAN,out_path_set);
	sscanf(T_STRING,L_SCAN,log_ctrl_set);
		
	char *idx=strstr(T_STRING,"l=");
	if(idx)sscanf(idx,"l=%"STR(MAX_TYPE)"s",log_ctrl_set);
	idx=strstr(T_STRING,"op=");
	if(idx)sscanf(idx,"op=%"STR(MAX_PNL)"s",out_path_set);
	printf("idx:%s\n",idx);
	printf("out_path_set=%s\n",out_path_set);
	printf("log_ctrl_set=%s\n",log_ctrl_set);	
	return 0;
}
