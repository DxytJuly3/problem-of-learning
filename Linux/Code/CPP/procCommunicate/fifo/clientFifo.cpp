// 命名管道客户端, 即写入端, 不参与命名管道的创建
#include "common.h"

using std::cout;
using std::endl;
using std::cerr;

int main() {
    int pipeFd = open(IPC_PATH, O_WRONLY);      // 只写打开命名管道, 不参与创建
    if(pipeFd < 0) {
        cerr << "open fifo error" << endl;
        return 1;
    }

    char line[1024];        // 用于接收命令行的信息
    while (true) {
        printf("请输入消息 $ ");
        fflush(stdout);         // printf没有刷新stdout, 所以手动刷新
        memset(line, 0, sizeof(line));
        if(fgets(line, sizeof(line), stdin) != nullptr) {
            // 由于fgets 会接收 回车, 所以将 line的最后一位有效字符设置为 '\0'
            line[strlen(line) - 1] = '\0';
            // 向命名管道写入信息
            write(pipeFd, line, strlen(line));
        }
        else {
            break;
        }
    }
    close(pipeFd);
    cout << "客户端(写入端)推出啦" << endl;

    return 0;
}