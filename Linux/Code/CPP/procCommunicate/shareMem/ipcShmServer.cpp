// ipcShmServer 服务端代码, 即 接收端
// 需要创建、删除共享内存块
#include "common.hpp"
using std::cout;
using std::endl;
using std::cerr;

int main() {
    // 0. 创建共享内存块
    int key = ftok(PATH_NAME, PROJ_ID);

    cout << "Create share memory begin. " << endl;
    sleep(2);
    int shmId = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0666);
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
    while(cnt++ < 30) {
        cout << str << endl;
        sleep(1);
    }
    cout << "\nThe server has finished using shared memory. " << endl;

    sleep(1);
    // 3. 分离共享内存块
    int resDt = shmdt(str);
    if(resDt == -1) {
        cerr << "shmdt error" << endl;
    }
    cout << "Detach share memory success. \n" << endl;

    sleep(5);

    // 4. 删除共享内存块
    int res = shmctl(shmId, IPC_RMID, nullptr);
    if(res == -1) {
        cerr << "shmget error" << endl;
        exit(2);
    }
    cout << "Delete share memory success. " << endl;

    return 0;
}