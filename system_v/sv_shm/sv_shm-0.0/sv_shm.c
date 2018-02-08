#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <lzl/slog.h>
#include "sv_shm.h"

int sv_shmget(int *p_shmid,int size,int proj_id)
{
	key_t key={0};
	if(-1==(key=ftok("/",proj_id))){
		err("ftok fail,errno:%d[%s].",errno,strerror(errno));
		return -1;  
	}
	if(-1==(*p_shmid=shmget(key, size,0666 | IPC_CREAT))){
		err("shmget fail,errno:%d[%s].",errno,strerror(errno));
		return -2;  	
	}
	return 0;
}
/* --------------------------------------------------------------------------------
							说明
shmaddr和shmflg参数共同决定了共享内存区连接到调用进程的具体地址，规则如下：
shmaddr为空指针：连接的地址由系统内核决定，这是推荐的方法，具有可移植性。
shmaddr非空：此时还要根据shmflg参数是否指定SHM_RND标志进行判断：
没有指定SHM_RND：共享内存区连接到调用进程的shmaddr指定的地址；
指定SHM_RND：共享内存区连接到shmaddr指定的地址向下舍入SHMLBA的位置。
shmflg：除了上面说的SHM_RND外，还有可以指定SHM_RDONLY标志，限定只读访问。一般该标志置为0。
-------------------------------------------------------------------------------- */
int sv_shmat(void **p_shmaddr,int shmid)
{
	void *shmaddr=NULL;
	shmaddr=shmat(shmid,NULL,0);
	if((void *)-1==shmaddr){
		err("shmat fail,errno:%d[%s].",errno,strerror(errno));
		exit(-1);
	}
	*p_shmaddr=shmaddr;
	return 0;
}

int sv_shmdt(const void *shmaddr)
{
	if(-1==shmdt(shmaddr)){
		err("shmdt fail,errno:%d[%s].",errno,strerror(errno));
		return -1;
	}
	return 0;
}

int sv_shmdel(int shmid)
{
	if(-1==shmctl(shmid, IPC_RMID, 0)){
		err("shmctl IPC_RMID fail,errno:%d[%s].",errno,strerror(errno));
		return -1;  
	}
	return 0;
}
// --------------通用部分--------------------------<<

// --------------非通用部分------------------------<<