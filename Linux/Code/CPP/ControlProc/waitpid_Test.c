#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t id = fork();

    if(id == 0) {
        printf("我是子进程, 我的pid: %d\n", getpid());
        sleep(10);
        int cnt = 5;
        while(cnt) {
            printf("我是子进程, 我的pid: %d, 我还有 %ds退出\n", getpid(), cnt);
            cnt--;
            sleep(1);
        }
    }
    else {
        printf("我是父进程, 我正在准备等待子进程\n");
        int status = 0;
        pid_t pidGet = waitpid(id, &status, 0);
        if(pidGet > 0) {
            if(WIFEXITED(status)) {
                printf("子进程正常退出, 退出码为: %d\n", WEXITSTATUS(status));
            }
            else {
                printf("子进程正常退出, 退出码为: %d\n", WEXITSTATUS(status));
                printf("子进程异常退出, 退出信号为: %d\n", WTERMSIG(status));
            }
        }
//            printf("等待成功, 子进程的退出码是 %d, 退出信号是 %d\n", (status>>8)&0xFF, status&0x7F);
    }

    return 0;
}
