#include <unistd.h>
#include "px_shm.c"
#define T_POSIX_SHM "/ttt1"
char *t_shm=NULL;
int read_handle(void *args)
{	
	char **argv=(char **)args;
	px_shm_get((void**)&t_shm,T_POSIX_SHM);
	inf("t_shm content is:%s .",t_shm);
	do{
		// sleep(1);
	}while(0);		
	return 0;
}
int write_handle(void *args)
{	
	char **argv=(char **)args;
	IS_ARG_COUNT_LESS_THAN(2);
	px_shm_get((void**)&t_shm,T_POSIX_SHM);
	memcpy(t_shm,argv[2],PX_SHM_INIT_SIZE);
	inf("t_shm content is:%s .",t_shm);
	return 0;
}
misc_cmd_t misc_cmd_tbl[]={
	{"read",		read_handle					},
	{"write",		write_handle				},
};
int main(int argc,char **argv)
{
	log_init("l=11111");
	IS_ARG_COUNT_LESS_THAN(1);
	int i=0;
	int cmd_count=sizeof(misc_cmd_tbl)/sizeof(misc_cmd_tbl[0]);
	for(i=0;i<cmd_count;i++){
		if(!strcmp(argv[1],misc_cmd_tbl[i].cmd)){
			int ret=0;
			ret=misc_cmd_tbl[i].handle(argv);
			if(ret<0){
				return -2;
			}
			return 0;
		}
	}
	return -3;
}



