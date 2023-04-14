#include <iostream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using std::cout;
using std::endl;
using std::string;

void printTid(const char* threadName, const pthread_t& tid) {
    cout << threadName << " is runing, "
         << "tid: " << tid << ", pid: " << getpid() << endl;
}

void* callBack1(void* args) {
    char* threadName = (char*)args;
    //pthread_t tid = (pthread_t)args;  // 这里如果想要向主线程发送取消请求, 则args需要是主线程的id
    int cnt = 5;
    while (true) {
        printTid("thread_1", pthread_self());
        //pthread_cancel(pthread_self());

        sleep(1);
        cnt--;
        if (cnt == 0) {
            // pthread_cancel(tid);                      // 新线程向主线程发送取消请求
            pthread_cancel(pthread_self());            // 新线程向自己发送取消请求
            // pthread_exit((void*)123);
            //  int i = 1;
            //  i /= 0;
            // int* pi = nullptr;
            //*pi = 123;
        }
    }
    // cout << "thread_1 is over" << endl;

    // int* ret = new int(123);
    // return (void*)ret;
}

int main() {
    pthread_t tid1;

    pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");
    // sleep(2);
    // pthread_cancel(tid1);
    // cout << "main thread cancel thread_1" << endl;

    // while(true) {
    //     printTid("main thread", pthread_self());
    //     sleep(1);
    // }

    // sleep(10);

    void* ret = nullptr;
    pthread_join(tid1, &ret);
    cout << "main thread join thread_1 , ready to print thread_1 ret" << endl;
    sleep(2);
    cout << "print thread_1 ret: " << (long long)ret << endl;

    // sleep(15);  // 等15s，让thread_1运行完

    // void* ret = nullptr;
    // pthread_join(tid1, &ret);
    // cout << "main thread join thread_1 , ready to print thread_1 ret" << endl;

    // sleep(2);

    // cout << "print thread_1 ret: " << *((int*)ret) << endl;
    // delete (int*)ret;

    // cout << "thread_1 id: " << tid1 << endl;

    // while (true) {
    //     cout << " 主线程运行: " << getpid() << " " << endl;
    //     sleep(1);
    // }

    // void* ret = nullptr;
    // pthread_join(tid1, &ret);

    // cout << "main thread join thread_1 , ready to print thread_1 ret" << endl;

    // sleep(2);
    // cout << (char*)ret << endl;

    return 0;
}