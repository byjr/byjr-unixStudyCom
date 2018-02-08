#include <string.h>
#include <stdio.h>
int main(void)
{
	FILE* stream;
	_G_va_list __arg;
	char string[]="Thisisatest";
	fpos_t filepos;
	/*openafileforupdate*/
	stream=fopen("DUMMY.FIL","w+");
	/*writeastringintothefile*/
	fwrite(string,strlen(string),3,stream);
	/*reportthefilepointerposition*/
	fgetpos(stream,&filepos);
	printf("The file pointer is at byte	%ld\n",filepos.__pos);
	fclose(stream);
	while(1);
	return 0;
}