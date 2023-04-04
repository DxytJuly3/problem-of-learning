#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cerrno>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
using std::cout;
using std::cerr;
using std::endl;
using std::string;

int cnt = 0;

void handler(int signo) {
    cout << "我是进程, pid: " << getpid() << ", 我捕获到一个信号：" << signo << endl;
    cout << "count: " << cnt << endl;
    exit(1);
}

void usage(const string& proc) {
    cout << "Usage:\n\t" << proc << " sig pid" << endl;
}

// 模拟实现 kill命令
// ./mykill sig pid
int main(int argc, char* argv[]) {
    signal(SIGALRM, handler);
    alarm(1);           // 设置 1s 的闹钟

    while (true) {
        cnt++;
    }

    return 0;
    // while (true) {
    //     cout << "count: " << cnt++ << endl;
    // }

    // return 0;
   
    // signal(2, handler);
    // signal(SIGABRT, handler);

    // while (true) {      // 循环给自己发送 信号2
    //     raise(2);
    //     sleep(1);
    //     if (cnt > 5)
    //         abort();
    // }
    
    // return 0;
    // if (argc != 3) {
    //     usage(argv[0]);             // argv[0] 即为命令行的第一个字符串
    //     exit(1);
    // }

    // if (kill( (pid_t)atoi(argv[2]), atoi(argv[1]) ) == -1) {
    //     cerr << "kill error, " << strerror(errno) << endl;
    //     exit(2); 
    // }

    // return 0;

    // signal(9, handler);
    // sleep(1);
    // cout << "进程已经设置完了" << endl;

    // while (true)
    // {
    //     cout << "我是一个正在运行中的进程: " << getpid() << endl;
    //     sleep(1);
    // }

    // return 0;
}