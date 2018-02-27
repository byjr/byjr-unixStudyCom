#include "un_fork.c"
char *cmd={
	"ping www.baidu.com -c 2",
	// "find ./ -name *.c",
	// "ls -l"
};
int var=111;
int main(int argc, char *argv[]){
	log_init("l=11111");
	int ret=vfexec(cmd);
	if(ret<0)show_errno(0,"vfexec");
	return 0;
}