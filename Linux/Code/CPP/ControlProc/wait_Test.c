#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t id = fork();

    if(id == 0) {
        int cnt = 15;
        while(cnt) {
            printf("我是子进程, %ds后进入Z状态, 变为僵尸进程\n", cnt);
            sleep(1);
            cnt--;
        }
        printf("我是子进程, 已进入僵尸状态\n");
        exit(123);
    }
    else {
        sleep(6);
        printf("我是父进程, 还未等待子进程\n");
        //sleep(19);
//        int cnt = 5;
//        while(cnt) {
//            printf("%ds后, 等待子进程\n", cnt);
//            cnt--;
//            sleep(1);
//        }
        pid_t waitPid = wait(NULL);
        printf("我是父进程, 已等待子进程, 等待的进程的PID= %d\n", waitPid);
        sleep(15);              // 父进程等待子进程之后, 先不要结束
    }

    return 0;
}
