#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t id = fork();
    if(id == 0) {
        printf("我是子进程, pid :%d\n", getpid());
        execl("/usr/bin/ls", "ls", "-l", "-a");
        printf("我是子进程, pid :%d\n", getpid());
    }
    else {
        pid_t ret = wait(NULL);
        if(ret > 0) {
            printf("我是父进程, 等待子进程成功\n");
        }
        else {
            printf("等待子进程失败\n");
        }
    }

    return 0;
}
