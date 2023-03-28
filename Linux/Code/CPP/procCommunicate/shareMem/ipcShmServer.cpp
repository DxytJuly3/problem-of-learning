#include "common.hpp"
using std::cout;
using std::endl;
using std::cerr;

int main() {
    int key = ftok(".ipcShm", 0x14);
    int shmId = shmget(key, 4096, IPC_CREAT | IPC_EXCL);
    if(shmId == -1) {
        cerr << "shmget error" << endl;
        exit(1);
    }
    
    cout << "shmget success, key: " << key << " , shmId: " << shmId << endl;

    return 0;
}