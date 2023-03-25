#include <iostream>
#include <unistd.h>
#include <cstring>

int main() {
    // 父进程 pipe()系统调用, 打开管道
    int pipeFd[2] = {0};
    int ret = pipe(pipeFd);
    if(ret != 0) {
        std::cerr << "pipe error" << std::endl;
        return 1;
    }

    // 创建子进程
    // 并让 父进程 通过管道 向子进程 传输数据
    pid_t id = fork();
    if(id < 0) {
        std::cerr << "fork error" << std::endl;
        return 2;
    }
    else if(id == 0) {
        // 子进程执行代码
        // 子进程接收数据, 所以关闭只写端口 pipeFd[1]
        close(pipeFd[1]);
        char buffer[1024];
        while (true)
        {    
            memset(buffer, 0, 1024);
            sleep(15);
            ssize_t s = read(pipeFd[0], buffer, sizeof(buffer)-1);
            if(s > 0) {
                // 读取成功
                buffer[s] = '\0';
                std::cout << buffer << std::endl;
            }
            else if(s == 0) {
                // 读取结束       
                std::cout << "父进程写入结束, 子进程读取也结束！" << std::endl;
                break;
            }
            else {
                // 读取失败
            }
        }
    }
    else {
        // 父进程执行代码
        // 父进程发送数据, 所以关闭只读端口 pipeFd[0]
        close(pipeFd[0]);
        // 父进程每秒写入一句, 共5句
        const char* msg = "你好子进程, 我是父进程, 我通过管道跟你通信, 此次发送编号:: ";
        int cnt = 0;
        while(true) {
            char sendBuffer[1024];
            sprintf(sendBuffer, "%s %d", msg, cnt);
            //sleep(10);
            write(pipeFd[1], sendBuffer, strlen(sendBuffer));
            cnt++;
            std::cout << "父进程写入:: " << cnt << " 次" << std::endl;
        }
        std::cout << "父进程写入完毕" << std::endl;
    }

    return 0;
}
