// ipcShmClient 客户端代码, 即 发送端
// 不参与共享内存块的创建与删除
#include "common.hpp"
using std::cout;
using std::endl;
using std::cerr;

int main() {
    // 0. 获取共享内存块
    int key = ftok(PATH_NAME, PROJ_ID);
    cout << "Get share memory begin. " << endl;
    sleep(1);
    int shmId = shmget(key, SHM_SIZE, IPC_CREAT);
    if(shmId == -1) {
        cerr << "shmget error" << endl;
        exit(1);
    }
    cout << "Creat share memory success, key: " << key << " , shmId: " << shmId << endl;

    // 1. 连接共享内存块
    sleep(2);
    char* str = (char*)shmat(shmId, nullptr, 0);
    if(str == (void*)-1) {
        cerr << "shmat error" << endl;
        exit(2);
    }
    cout << "Attach share memory success. " << endl;

    // 2. 使用共享内存块
    int cnt = 0;
    while (cnt < 26) {
        str[cnt] = 'A' + cnt;
        cnt++;
        str[cnt] = '\0';
        sleep(1);
    }
    cout << "\nThe client has finished using shared memory. " << endl;

    // 3. 分离共享内存块
    int res = shmdt(str);
    if(res == -1) {
        cerr << "shmdt error" << endl;
    }
    cout << "Detach share memory success. " << endl;

    sleep(5);

    return 0;
}