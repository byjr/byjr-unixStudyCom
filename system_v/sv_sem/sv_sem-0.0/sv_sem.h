#ifndef SYSV_SEM_H_
#define SYSV_SEM_H_ 	1
#define __USE_GNU 		1
#define _GNU_SOURCE		1
#include <sys/sem.h>

/* -------------------------
typedef enum PROJ_ID_T{
	INIT_VALUE_PROJ_ID,	
	U2I_MSG,
	I2U_MSG,
	MAX_PROJ_ID
}proj_id_t;

typedef struct sem_ST{
	char *cmd[64];
	char *text[1024];
}sem_st;
------------------------ */
typedef union SEMUN_T{
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO
							   (Linux-specific) */
}semun_t;
int sv_semget(int *p_semid,int count,int proj_id);
int sv_semop(int semid,int n,int val);
int sv_semop_nowait(int semid,int n,int val);
int sv_semtimedop(int semid,int n,int val,int sec);
int sv_semset(int semid,int n,int val);
int sv_semdel(int semid,int n);


// --------------通用部分--------------------------<<

// --------------非通用部分------------------------<<
#define SEM_CMD_SIZE 	64
#define SEM_TEXT_SIZE 	1024
typedef enum PROJ_ID_T{
	INIT_VALUE_PROJ_ID,	
	TTT_SEM,
	TTT_SHM,	
	TTT_MSG,	
	MAX_PROJ_ID
}proj_id_t;

#endif