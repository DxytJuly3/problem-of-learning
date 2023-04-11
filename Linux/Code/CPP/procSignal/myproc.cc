#include <cassert>
#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using std::cout;
using std::endl;

int flags = 0;

void handler(int signo) {
    cout << "子进程退出, 我收到了信号: " << signo << ", 我是: " << getpid() << endl;
    // cout << "获取到一个信号,信号的编号是: " << signo << endl;
    // flags = 1;
    // cout << "我修改了flags: 0->1" << endl;
}

void freeChild(int signo) {
    assert(signo == SIGCHLD);

    while (true) {
        pid_t id = waitpid(-1, nullptr, WNOHANG);
        if (id > 0) {
            cout << "父进程等待子进程成功, child pid: " << id << endl;
        }
        else if(id == 0){
            cout << "还有子进程在运行, 但是没有子进程退出, 父进程要去做自己的事了 " << endl;
            break;
        }
        else {
            cout << "父进程等待所有子进程结束" << endl;
            break;
        }
    }
}

void handler1() {
    cout << "处理 1信号" << endl;
}
void handler2() {
    cout << "处理 2信号" << endl;
}
void handler3() {
    cout << "处理 3信号" << endl;
}
void handler4() {
    cout << "处理 4信号" << endl;
}
void handler5() {
    cout << "处理 5信号" << endl;
}

void handlerAll(int signo) {
    switch (signo) {
    case 1:
        handler1();
        break;
    case 2:
        handler2();
        break;
    case 3:
        handler3();
        break;
    case 4:
        handler4();
        break;
    case 5:
        handler5();
        break;
    default:
        break;
    }
}

int main() {
    // signal(SIGCHLD, handler);
    // signal(SIGCHLD, freeChild);
    signal(SIGCHLD, SIG_IGN);
    for (int i = 0; i < 5; i++) {
        pid_t id = fork();
        if (id == 0) {
            // 子进程
            int cnt = 0;
            if(i < 2)
                cnt = 5;        // 前2个子进程 5s就退出
            else
                cnt = 30;       // 后3个子进程 30s 退出
            while (cnt) {
                cout << "我是子进程, pid: " << getpid() << ", cnt: " << cnt-- << endl;
                sleep(1);
            }
            cout << "子进程退出, 进入僵尸状态" << endl;
            exit(0);
        }
    }

    // 父进程
    while (true) {
        cout << "我是父进程, pid: " << getpid() << endl;
        sleep(1);
    }

    return 0;

    // signal(2, handler);

    // while(!flags);
    // // 未接收到信号时, flags 为 0, !flags 恒为真, 所以会死循环
    // cout << "此进程正常退出" << endl;

    // return 0;
    // // 先定义两个 struct sigaction 用于传参
    // struct sigaction act, oact;

    // // 初始化 act
    // act.sa_handler = handler;
    // act.sa_flags = 0;
    // sigemptyset(&act.sa_mask);
    // sigaddset(&act.sa_mask, 3);         // 在 act.sa_mask 中设置 3信号

    // // sigaction 捕捉 2信号
    // sigaction(2, &act, &oact);

    // while (true) {
    //     cout << "I am a process, pid: " << getpid() << endl;
    //     sleep(1);
    // }

    // return 0;
}