#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<signal.h>
#include "ring_buf.h"
#include<lzl/slog.h>
#include "ring_buf.c"
ring_buf_t *ring_buf=NULL;
rb_unit_t rb_unit={1};
void signal_handle(int signo){
	int ret=0;
	switch(signo){	
	case 34:{
		rb_flag_query(ring_buf);
		break;
	}
	case 35:{
		rb_unit_t *p_unit=NULL;
		p_unit=rb_read(ring_buf);
		if(p_unit){
			inf("flag=%d",p_unit->flag);			
		}
		rb_flag_query(ring_buf);
		break;
	}
	case 36:{
		rb_write(ring_buf,&rb_unit);
		rb_flag_query(ring_buf);
		break;		
	}		
	default:
		inf("recive signal:%d!",signo);	
		break;
	}
}
int main(){
	int ret=0,i=0;
	log_init(NULL);
	for(i=SIGRTMIN;i<=SIGRTMAX;i++){
		signal(i,signal_handle);		
	}
	ring_buf=rb_create(5);
	if(!ring_buf)return -1;
	inf("succeed ring buf in %08x",ring_buf);
	while(1)pause();
}