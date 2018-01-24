#ifndef SYSV_SHM_H_
#define SYSV_SHM_H_ 1
/* -------------------------
typedef enum PROJ_ID_T{
	INIT_VALUE_PROJ_ID,	
	U2I_MSG,
	I2U_MSG,
	MAX_PROJ_ID
}int;

typedef struct SHM_ST{
	char *cmd[64];
	char *text[1024];	
}shm_st;
------------------------ */

int sv_shmget(int *p_shmid,int size,int proj_id);
int sv_shmat(void **p_shmaddr,int shmid);
int sv_shmdt(const void *shmaddr);
int sv_shmdel(int shmid);

// --------------通用部分--------------------------<<

// --------------非通用部分------------------------<<
#define SHM_CMD_SIZE 		64
#define SHM_TEXT_SIZE 		1024
#define LOCK_SEM_SIPC		3
typedef struct SHM_ST{
	char cmd[SHM_CMD_SIZE];
	char txt[SHM_TEXT_SIZE];	
}shm_st;

#endif