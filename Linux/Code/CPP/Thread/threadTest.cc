#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void* threadFun1(void* args) {
    string str = (char*)args;
    while (true) {
        cout << str << ": " << getpid() << " " << endl;
        sleep(1);
    }
}

void* threadFun2(void* args) {
    string str = (char*)args;
    while (true) {
        cout << str << ": " << getpid() << " " << endl;
        sleep(1);
    }
}

int main() {
    pthread_t tid1, tid2;

    pthread_create(&tid1, nullptr, threadFun1, (void*)"thread_1");
    pthread_create(&tid2, nullptr, threadFun2, (void*)"thread_2");

    pid_t id = fork();
    if (id == 0) {
        while (true) {
            cout << "我是子进程: " << getpid() << endl;
            sleep(1);
        }
    }

    while (true) {
        cout << " 主线程运行: " << getpid() << " " << endl;
        sleep(1);
    }

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);

    return 0;
}