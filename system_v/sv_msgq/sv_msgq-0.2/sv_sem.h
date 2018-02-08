#ifndef MY_SEM_H_
#define MY_SEM_H_ 1

int my_sem_init(sem_t *p_sem,int pshared,unsigned int value);
int my_sem_open(sem_t **pp_sem,char *path,unsigned int value);
int my_sem_close(sem_t *p_sem);
int my_sem_getvalue(unsigned int *p_val,sem_t *p_sem);
int my_sem_post(sem_t *p_sem,unsigned int max);
int my_sem_wait(sem_t *p_sem);
int my_sem_trywait(sem_t *p_sem);
int my_sem_trywait(sem_t *p_sem);
int my_sem_timedwait(sem_t *p_sem,int sec);
int my_sem_destroy(sem_t *p_sem);
int my_sem_unlink(const char* path);
#define SLOG_SEM_PATH "/slog_sem_path2"
#endif