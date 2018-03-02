#include "un_fifo.h"
static int fifo_fd=0;

// 1.若以只读或者只写方式打开fifo 会卡在open位置

int un_fifo_init(char *path,char *mode){
	int ret=access(FIFO_PATH, F_OK);
	if(ret<0){
		ret=un_mkfifo(FIFO_PATH,0777);
		if(-1==ret)return -1;
	}
	inf("fifo is OK !");
	int style=mode[0]=='r'?O_RDONLY:mode[0]=='w'?O_WRONLY:O_RDWR;
	fifo_fd=un_open(FIFO_PATH,style|O_EXCL,0777);
	if(fifo_fd<0) return -1;
	inf("open fifo succeed!");
	return 0;
}
int un_fifo_read(char *buf,size_t size){
	size_t ret=un_read(fifo_fd,buf,size);
	if(ret<1) return -1;
	return 0;
}
// 2.若指定的写入长度大于数据长度会自动在行未加上换行符
int un_fifo_write(char *buf,size_t size){
	size_t ret=un_write(fifo_fd,buf,size);
	if(ret<1) return -1;
	return 0;
}
int un_fifo_write_str(char *ptr){
	if(!(ptr && ptr[0])) {
		err("ptr is invalid!");
		return -1;
	}
	size_t ret=un_write(fifo_fd,ptr,strlen(ptr));
	if(ret<1) return -2;
	return 0;
}		
