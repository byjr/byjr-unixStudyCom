#ifndef POSIX_SEM_H_
#define POSIX_SEM_H_ 1
#include <semaphore.h>
int px_seminit(sem_t *p_sem,int pshared,unsigned int value);
int px_semopen(sem_t **pp_sem,char *path,unsigned int value);
int px_semclose(sem_t *p_sem);
int px_semgetvalue(unsigned int *p_val,sem_t *p_sem);
int px_sempost(sem_t *p_sem,unsigned int max);
int px_semwait(sem_t *p_sem);
int px_semtrywait(sem_t *p_sem);
int px_semtimedwait(sem_t *p_sem,int sec);
int px_semdestroy(sem_t *p_sem);
int px_semunlink(const char* path);

#define SLOG_SEM_PATH "/slog_sem_path2"
//#define MAX_BUF_SIZE 1024
#endif