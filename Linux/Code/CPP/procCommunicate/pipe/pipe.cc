#include <iostream>
#include <unistd.h>
#include <ctime>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <sys/wait.h>
#include <sys/types.h>
#include <cassert>
using std::cout;
using std::endl;
using std::cerr;
using std::vector;
using std::string;
using std::unordered_map;
using std::pair;

typedef void (*functor)();      // typedef 函数指针为 functor

vector<functor> functors;        // 创建函数指针数组, 用来存储函数指针

unordered_map<uint32_t, string> info;       // 用来存储 functors 对应元素存储的任务的信息

typedef pair<pid_t, int> elem;      // elem用来存储 子进程pid 以及对应管道的写入端fd
// first 存储子进程pid, second 存储对应管道写端fd

// 只用函数举例, 不实现具体功能
void f1() {
    cout << "这是一个处理日志的任务, 执行的进程 ID [" << getpid() << "]"
         << "执行时间是[" << time(nullptr) << "]\n" << endl;
    //
}
void f2() {
    cout << "这是一个备份数据任务, 执行的进程 ID [" << getpid() << "]"
         << "执行时间是[" << time(nullptr) << "]\n" << endl;
}
void f3() {
    cout << "这是一个处理网络连接的任务, 执行的进程 ID [" << getpid() << "]"
         << "执行时间是[" << time(nullptr) << "]\n" << endl;
}

void loadFunctor() {
    info.insert({functors.size(), "处理日志"});
    functors.push_back(f1);

    info.insert({functors.size(), "备份数据"});
    functors.push_back(f2);

    info.insert({functors.size(), "处理网络连接"});
    functors.push_back(f3);
}

void childProcWork(int readFd) {
    sleep(1);
    cout << "进程 [" << getpid() << "] 开始工作" << endl;
    
    while (true) {
        uint32_t operatorType = 0;
        ssize_t ret = read(readFd, &operatorType, sizeof(uint32_t));
        if(ret == 0) {
            cout << "父进程任务派完了……" << endl;
            break;
        }
        assert(ret == sizeof(uint32_t));
        (void)ret;

        if (operatorType < functors.size()) {
            functors[operatorType]();
        }
        else {
            cout << "BUG ? operatorType:: " << operatorType << endl;
        }
    }
    cout << "进程 [" << getpid() << "] 结束工作" << endl;
}

void blanceAssignWork(const vector<elem> &processFds) {
    srand((long long)time(nullptr));        // 设置随机数种子

    // 随机对子进程 随机分配任务 num 次
    int cnt = 1;
    //int num = 15;
    while (/*cnt < num+1*/ true) {
        sleep(1);
        // 随机选择子进程
        uint32_t pickProc = rand() % processFds.size();
        // 随机选择任务
        uint32_t pickWork = rand() % functors.size();

        write(processFds[pickProc].second, &pickWork, sizeof(uint32_t));

        cout << "父进程给进程: "  << processFds[pickProc].first << " 派发任务->" << info[pickWork] <<
             ", 对应管道写端fd: " << pickProc << ", 第 " << cnt << " 次派发" << endl;
        
        cnt++;
    }
    sleep(2);
}

int main() {
    // 0. 加载任务列表
    loadFunctor();

    // 循环创建5个子进程以及对应的管道
    vector<elem> assignMap;         // 子进程pid与对应管道的fd记录 
    int processNum = 5;
    for(int i = 0; i < processNum; i++) {
        int pipeFd[2] = {0};

        if(pipe(pipeFd) != 0) {
            cerr << "第 " << i << " 次, pipe 错误" << endl;
        }

        pid_t id = fork();
        if(id == 0) {
            // 子进程执行代码
            close(pipeFd[1]);

            childProcWork(pipeFd[0]);        // 子进程功能具体函数

            close(pipeFd[0]);
            exit(0);
        }
        // 因为在if(id == 0) 的最后, 执行了 exit(0); 所以子进程不会跳出 if(id == 0) 的内部
        // 所以下面都为父进程执行的代码
        // 父进程执行代码
        close(pipeFd[0]);
        assignMap.push_back(elem(id, pipeFd[1]));     
        // elem(id, pipeFd[1]) 创建pair<uint32_t, uint32_t> 匿名对象, 存储 此次创建子进程pid 和 打开管道的写端fd
        // 并存入 vector 中
    }
    cout << "创建子进程完毕" << endl;
    cout << "父进程, 开始随机给子进程 随机派发任务\n" << endl;

    sleep(1);
    blanceAssignWork(assignMap);        // 父进程派发任务函数


    // 回收所有子进程
    for(int i = 0; i < processNum; i++) 
        close(assignMap[i].second);
    
    for(int i = 0; i < processNum; i++)  {
        if(waitpid(assignMap[i].first, nullptr, 0)) {
            cout << "等待子进程_pid: " << assignMap[i].first << ", 等待成功. Number: " << i << endl;
        }
    }

    return 0;
    
    /* 匿名管道控制单个进程 */
    // // 0. 加载任务列表
    // loadFunctor();      // 加载任务到数组中, 即 加载任务列表

    // // 1. 创建管道
    // int pipeFd[2] = {0};
    // if(pipe(pipeFd) != 0) {
    //     cerr << "pipe error" << endl;
    // }

    // // 2. 创建子进程
    // pid_t id = fork();
    // if(id < 0) {
    //     cerr << "fork error" << endl;
    // }
    // else if(id == 0) {
    //     // 子进程执行代码
    //     // 关闭 写入端
    //     close(pipeFd[1]);
    //     while(true) {
    //         // 与写入端写入的数据相同的数据类型
    //         uint32_t operatorType = 0;
    //         ssize_t ret = read(pipeFd[0], &operatorType, sizeof(uint32_t));
    //         if(ret == 0) {
    //             cout << "父进程任务派完了, 我要走了……" << endl;
    //             break;
    //         }
    //         // 这里的read返回值 ret, 大小应该是sizeof(uint32_t), 可以断言判断一下
    //         assert(ret == sizeof(uint32_t));
    //         (void)ret;
    //         // 这里将ret强转为void类型, 是为了解决release编译模式中, 有可能因为ret没被使用而出现的waring
    //         // assert() 只在debug编译模式中有效, 使用release模式编译的话, assert()就没有了
    //         // 所以会出现 ret没被使用的情况

    //         if(operatorType < functors.size()) {
    //             // 如果从管道中接受的数据, 在functors(任务列表)的范围内, 则执行任务
    //             functors[operatorType]();
    //         }
    //         else {
    //             // 否则, 就可能出 bug 了
    //             cout << "BUG ? operatorType:: " << operatorType << endl;
    //         }
    //     }
    //     // 执行任务完成, 关闭读取端
    //     close(pipeFd[0]);
    //     exit(0);
    // }
    // else {
    //     // 父进程执行代码
    //     // 随机向子进程分配任务, 则需要先设定一个 srand
    //     srand((long long)time(nullptr));        // 用时间设定
    //     close(pipeFd[0]);
    //     int num = functors.size();
    //     int cnt = 1;               
    //     while (cnt <= 10)   // 随机派发 10 次任务
    //     {
    //         uint32_t commandCode = rand() % num;    // 随机生成 派发的任务编号

    //         cout << "父进程已派发任务:: " << info[commandCode] << ", 第 " << cnt << " 次派发" << endl;
    //         cnt++;
            
    //         write(pipeFd[1], &commandCode, sizeof(uint32_t));       // 向管道中写入任务编号
    //         sleep(1);
    //     }
    //     // 派发完成之后, 关闭写入端, 并回收子进程
    //     close(pipeFd[1]);
    //     pid_t result = waitpid(id, nullptr, 0);
    //     if(result) {
    //         cout << "waitpid success" << endl;
    //     }
    // }

    // return 0;


    /* 匿名管道的创建以及基本使用 */
    // // 父进程 pipe()系统调用, 打开管道
    // int pipeFd[2] = {0};
    // int ret = pipe(pipeFd);
    // if(ret != 0) {
    //     std::cerr << "pipe error" << std::endl;
    //     return 1;
    // }

    // // 创建子进程
    // // 并让 父进程 通过管道 向子进程 传输数据
    // pid_t id = fork();
    // if(id < 0) {
    //     std::cerr << "fork error" << std::endl;
    //     return 2;
    // }
    // else if(id == 0) {
    //     // 子进程执行代码
    //     // 子进程接收数据, 所以关闭只写端口 pipeFd[1]
    //     close(pipeFd[1]);
    //     char buffer[1024];
    //     while (true)
    //     {    
    //         memset(buffer, 0, 1024);
    //         sleep(15);
    //         ssize_t s = read(pipeFd[0], buffer, sizeof(buffer)-1);
    //         if(s > 0) {
    //             // 读取成功
    //             buffer[s] = '\0';
    //             std::cout << buffer << std::endl;
    //         }
    //         else if(s == 0) {
    //             // 读取结束       
    //             std::cout << "父进程写入结束, 子进程读取也结束！" << std::endl;
    //             break;
    //         }
    //         else {
    //             // 读取失败
    //         }
    //     }
    // }
    // else {
    //     // 父进程执行代码
    //     // 父进程发送数据, 所以关闭只读端口 pipeFd[0]
    //     close(pipeFd[0]);
    //     // 父进程每秒写入一句, 共5句
    //     const char* msg = "你好子进程, 我是父进程, 我通过管道跟你通信, 此次发送编号:: ";
    //     int cnt = 0;
    //     while(true) {
    //         char sendBuffer[1024];
    //         sprintf(sendBuffer, "%s %d", msg, cnt);
    //         //sleep(10);
    //         write(pipeFd[1], sendBuffer, strlen(sendBuffer));
    //         cnt++;
    //         std::cout << "父进程写入:: " << cnt << " 次" << std::endl;
    //     }
    //     std::cout << "父进程写入完毕" << std::endl;
    // }

    // return 0;
}
