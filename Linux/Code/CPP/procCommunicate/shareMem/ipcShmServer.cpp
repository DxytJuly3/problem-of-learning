// ipcShmServer 服务端代码, 即 接收端
// 需要创建、删除共享内存块
// 需要创建、删除命名管道
#include "common.hpp"
using std::cout;
using std::endl;
using std::cerr;

int main() {
    // 0. 创建命名管道
    CreatFifo();
    int fd = Open(FIFO_FILE, READER);       // 只读打开命名管道
    assert(fd >= 0);

    // 1. 创建共享内存块
    int key = ftok(PATH_NAME, PROJ_ID);
    if(key == -1) {
        cerr << "ftok error. " << strerror(errno) << endl;
        exit(1);
    }

    cout << "Create share memory begin. " << endl;
    int shmId = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
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
    cout << "Attach share memory success. \n" << endl;

    // 3. 使用共享内存块
    while(true) {
        if (Wait(fd) <= 0)
            break;              // 如果从管道读取数据失败, 或管道文件关闭, 则退出循环
        
        cout << str;
        sleep(1);
    }
    cout << "\nThe server has finished using shared memory. " << endl;

    sleep(1);
    // 3. 分离共享内存块
    int resDt = shmdt(str);
    if(resDt == -1) {
        cerr << "shmdt error" << endl;
        exit(4);
    }
    cout << "Detach share memory success. \n" << endl;

    // 4. 删除共享内存块
    int res = shmctl(shmId, IPC_RMID, nullptr);
    if(res == -1) {
        cerr << "shmget error" << endl;
        exit(5);
    }
    cout << "Delete share memory success. " << endl;

    // 5. 删除管道文件
    Close(fd, FIFO_FILE);
    cout << "Delete FIFO success. " << endl;

    return 0;
}