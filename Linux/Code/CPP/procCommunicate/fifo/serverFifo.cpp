// 命名管道服务端, 即读取端, 参与命名管道文件的创建
#include "common.h"

using std::cout;
using std::endl;
using std::cerr;

int main() {
    umask(0);
    if(mkfifo(IPC_PATH, 0666) != 0) {
        cerr << "mkfifo error" << endl;
        return 1;
    }

    int pipeFd = open(IPC_PATH, O_RDONLY);
    if(pipeFd < 0) {
        cerr << "open error" << endl;
        return 2;
    }

    cout << "命名管道文件, 已创建, 已打开" << endl;

    char buffer[1024];
    while (true) {
        ssize_t ret = read(pipeFd, buffer, sizeof(buffer)-1);
        if (ret == 0) {
            cout << "\n客户端(写入端)退出了, 我也退出吧";
            break;
        }
        else if (ret > 0) {
            cout << "客户端 -> 服务器 # " << buffer << endl;
        }
        else {
            cout << "read error: " << strerror(errno) << endl;
            break;
        }
    }

    close(pipeFd);
    cout << "\n服务端退出……" << endl;
    unlink(IPC_PATH);
    
    return 0;
}