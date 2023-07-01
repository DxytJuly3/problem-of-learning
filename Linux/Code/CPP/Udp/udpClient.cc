#include <cstdint>
#include <iostream>
#include <ostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>

#include "logMessage.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

void* recverAndPrint(void *args) {
    while (true)
    {
        int sockFd = *(int*)args;
        char buffer[1024];
        struct sockaddr_in temp;
        socklen_t len = sizeof(temp);
        ssize_t s = recvfrom(sockFd, buffer, sizeof(buffer), 0, (struct sockaddr*)&temp, &len);
        if (s > 0) {
            buffer[s] = 0;
            std::cout << nick_Name << "-" << buffer << std::endl;
        }
    }
}

static void Usage(const string porc) {
    cout << "Usage::\n\t" << porc << " server_IP server_Port nick_Name" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        Usage(argv[0]);
        exit(1);
    }

    // 先获取server_IP 和 server_Port 以及用户的昵称
    string server_IP = argv[1];
    uint16_t server_Port = atoi(argv[2]);
	static string nick_Name = argv[3];

    // 创建客户端套接字
    int sockFd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockFd < 0) {
        logMessage(FATAL, "socket() faild:: %s : %d", strerror(errno), sockFd);
        exit(2);
    }
    logMessage(DEBUG, "socket create success: %d", sockFd);

    // udpServer 到这里就 填充网络信息 并绑定到操作系统内核中了
    // 客户端需不需要这些操作?
    // 答案是肯定的.
    // 但是这些操作, 最好不要我们自己去做, 让操作系统自动帮我们完成.
    // 为什么?
    // 因为我们不需要手动指定IP以及端口号, 尤其是端口号. 如果手动指定了端口号 还有可能会造成其他问题
    // 并且, 客户端也不需要手动指定端口号, 还不如让操作系统随机生成端口号.
    // 服务器需要手动指定端口号, 是因为服务器是需要让其他主机去连接的, 所以知道且固定. 如果是随机的, 那服务器绝对没人用.
    // 而客户端一般没人会主动来连接、访问, 一般都是每次打开客户端绑定网络时, 就让操作系统代操作, 不然手动指定端口号 可能会影响其他的网络进程
    // 所以 我们不需要手动去填充 udpClient 的网络信息, 也不需要手动绑定

    // 填充服务器的网络信息
    // 从命令行接收到的服务器IP和端口号, 是需要填充在 sockaddr_in 结构体中的, 因为 向服务器网络进程发送信息需要使用
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(server_Port);
    server.sin_addr.s_addr = inet_addr(server_IP.c_str());

    // 通信
    string inBuffer;
    while (true) {
        cout << "Please Enter >> ";
        getline(cin, inBuffer);

        // 向 server 发送消息
        sendto(sockFd, inBuffer.c_str(), inBuffer.size(), 0,
               (const struct sockaddr*)&server, sizeof(server));
        // 在首次向 server 发送消息的时候, 操作系统会自动将Client网络进程信息 绑定到操作系统内核
    }

    close(sockFd);

    return 0;
}
