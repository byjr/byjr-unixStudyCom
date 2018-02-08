#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "un_flock.c"
int main()
{
    const char *lock_file = TEST_FILE_PATH;
    int n_fd = -1;
    int n_tries = 10;
 
    while (n_tries--)
    {
        // 创建锁文件
        n_fd = open(lock_file, O_RDWR | O_CREAT | O_EXCL, 0444);
        if (n_fd == -1)
        {
            // 创建失败
            printf("%d - Lock already present\n", getpid());
            sleep(2);
        }
        else
        {
            // 创建成功
            printf("%d - I have exclusive access\n", getpid());
            sleep(1);
            close(n_fd);
 
            // 删除锁文件，释放锁
            unlink(lock_file);
            sleep(2);
        }
    }
 
    return 0;
}