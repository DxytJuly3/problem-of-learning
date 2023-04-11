#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile int flags = 0;

void handler(int signo) {
    printf("获取到一个信号,信号的编号是: %d\n", signo);
    flags = 1;
    printf("我修改了flags: 0->1\n");
}

int main() {
    signal(2, handler);

    while (!flags)
        ;
    // 未接收到信号时, flags 为 0, !flags 恒为真, 所以会死循环
    printf("此进程正常退出\n");

    return 0;
}