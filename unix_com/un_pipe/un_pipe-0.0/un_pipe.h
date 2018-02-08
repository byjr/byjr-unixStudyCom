#ifndef UN_SIGNAL_H_
#define UN_SIGNAL_H_ 1
#include <lzl/px_sem.h>

#define LINE_BUF_LEN 1024
#define TEST_FILE_PATH "/tmp/file_lock.test"
#define CMD_SHM_NAME "/cmd_buf"
#define CMD_SEM_NAME "/cmd_trigger"##__FILE__

typedef enum cmd_return_t{
	CMD_NOT_FOUND =-2,
	CMD_FAILURE,
	CMD_SUCCEED,
	CMD_INIT_VAULUE
}cmd_return_t;

extern sem_t *p_sem;
#define  CMD_SEPARATOR "#"
#endif