// ipcShmClient 客户端代码, 即 发送端
// 不参与共享内存块的创建与删除
// 不参与命名管道的创建与删除
#include "common.hpp"
using std::cout;
using std::endl;
using std::cerr;

int main() {
    // 0. 打开命名管道
    int fd = Open(FIFO_FILE, WRITER);

    // 1. 获取共享内存块
    int key = ftok(PATH_NAME, PROJ_ID);
    if(key == -1) {
        cerr << "ftok error. " << strerror(errno) << endl;
        exit(1);
    }
    cout << "Get share memory begin. " << endl;
    sleep(1);
    int shmId = shmget(key, SHM_SIZE, IPC_CREAT);
    if(shmId == -1) {
        cerr << "shmget error" << endl;
        exit(2);
    }
    cout << "Creat share memory success, key: " << key << " , shmId: " << shmId << endl;

    // 2. 连接共享内存块
    sleep(2);
    char* str = (char*)shmat(shmId, nullptr, 0);
    if(str == (void*)-1) {
        cerr << "shmat error" << endl;
        exit(3);
    }
    cout << "Attach share memory success. " << endl;

    // 3. 使用共享内存块
    while (true) {
        printf("Please Enter $ ");
        fflush(stdout);
        ssize_t res = read(0, str, SHM_SIZE);       // 从标准输入读取数据写入到 共享内存(str) 中
        if(res > 0) {
            str[res] = '\0';
        }

        Signal(fd);     // 向命名管道写入信号
    }
    cout << "\nThe client has finished using shared memory. " << endl;

    // 3. 分离共享内存块
    int res = shmdt(str);
    if(res == -1) {
        cerr << "shmdt error" << endl;
        exit(4);
    }
    cout << "Detach share memory success. " << endl;

    return 0;
}