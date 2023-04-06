#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
using std::cout;
using std::cerr;
using std::endl;

int cnt = 0;
void handler(int signo) {
    cout << "我是进程, pid: " << getpid() << ", 我捕获到一个信号：" << signo << ", count: " << cnt++ << endl;
}

// 打印信号集的函数
void showSignals(sigset_t *signals) {
    // 使用 sigismember() 接口判断 31个普通信号是否在信号集中存在
    // 存在的信号输出1, 否则输出0
    for(int sig = 1; sig <= 31; sig++) {
        if(sigismember(signals, sig)) {
            cout << "1";
        }
        else {
            cout << "0";
        }
    }
    cout << endl;
}

int main() {
    // 先输出进程的 pid
    cout << "pid: " << getpid() << endl;

    // 定义sigsetmask()需要使用的 set 和 oldset, 并初始化
    sigset_t sigset, osigset;
    sigemptyset(&sigset);
    sigemptyset(&osigset);

    // 将进程的 所有普通信号屏蔽
    for(int sig = 1; sig <= 31; sig++) {
        sigaddset(&sigset, sig);
        signal(sig, handler);
    }
    sigprocmask(SIG_BLOCK, &sigset, &osigset);

    // 获取并打印进程的未决信号集
    sigset_t pendings;
    int cnt = 0;
    while(true) {
        sigemptyset(&pendings);
        sigpending(&pendings);
        showSignals(&pendings);
        sleep(1);
        cnt++;
        if(cnt == 30) {
            // 30s 后解除 2 3 5 6 8 信号的屏蔽
            sigemptyset(&sigset);
            sigaddset(&sigset, 2);
            sigaddset(&sigset, 3);
            sigaddset(&sigset, 5);
            sigaddset(&sigset, 6);
            sigaddset(&sigset, 8);
            sigprocmask(SIG_UNBLOCK, &sigset, &osigset);
        }
    }

    return 0;
}