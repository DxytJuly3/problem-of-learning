#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cerrno>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
using std::cout;
using std::cerr;
using std::endl;
using std::string;

int cnt = 0;

void handler(int signo) {
    cout << "我是进程, pid: " << getpid() << ", 我捕获到一个信号：" << signo << ", count: " << cnt++ << endl;
    //exit(1);
}

void usage(const string& proc) {
    cout << "Usage:\n\t" << proc << " sig pid" << endl;
}

// 模拟实现 kill命令
// ./mykill sig pid
int main(int argc, char* argv[]) {
    pid_t id = fork();
    if(id == 0) {
        // 子进程 除0错误, 应该接收到 8信号
        int i = 10;
        i /= 0;
        exit(1);
    }

    // 父进程等待子进程
    int status = 0;
    waitpid(id, &status, 0);
    printf("exitcode: %d, signo: %d, core dump flag: %d\n", (status>>8) & 0xFF, status & 0x7F, (status>>7)&0x1);

    return 0;

    // // 捕获进程, 自定义处理
    // signal(8, handler);

    // // 越界访问
    // int arr[10];
    // arr[100000] = 0;
    
    // // 解引用空指针
    // int* pi = nullptr;
    // *pi = 10;

    // 除0
    // int i = 10;
    // i /= 0;

    // return 0;
    // signal(SIGALRM, handler);
    // alarm(1);           // 设置 1s 的闹钟

    // while (true) {
    //     cnt++;
    // }

    // return 0;
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