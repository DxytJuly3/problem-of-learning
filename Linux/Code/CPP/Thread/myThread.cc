#include <iostream>
#include <unistd.h>
#include <pthread.h>
using std::cout;
using std::endl;

int tickets = 10000;
pthread_mutex_t mutex;

void* inqureTicket(void* args) {
    const char* name = static_cast<const char*>(args);

    int cnt = 10;
    while (cnt--) {
        if (tickets > 0) {
            usleep(100000);
            printf("%s: %lu 查到剩余票了, 还有: %d\n",name, pthread_self(), tickets);
            usleep(100000);
        }
        else {
            printf("没有票了\n", name);
            break;
        }
    }

    return nullptr;
}

void* grabTicket(void* args) {
    const char* name = static_cast<const char*>(args);

    while (true) {
        pthread_mutex_lock(&mutex);     // 在即将进入临界区时加锁
        if (tickets > 0) {
            // usleep(100);
            printf("%s: %lu 抢到票了, 编号为: %d\n", name, pthread_self(), tickets--);
            // usleep(100);
            pthread_mutex_unlock(&mutex);   // 在即将离开临界区时解锁
        }
        else {
            printf("没有票了, %s: %lu 放弃抢票\n", name, pthread_self());
            pthread_mutex_unlock(&mutex); // 在线程即将退出时解锁
            break;
        }
    }

    return nullptr;
}

int main() {
    pthread_mutex_init(&mutex, nullptr);

    pthread_t tid1, tid2, tid3, tid4;

    pthread_create(&tid1, nullptr, grabTicket, (void*)"thread_1");
    pthread_create(&tid2, nullptr, grabTicket, (void*)"thread_2");
    pthread_create(&tid3, nullptr, grabTicket, (void*)"thread_3");
    pthread_create(&tid4, nullptr, grabTicket, (void*)"thread_4");

    pthread_join(tid1, nullptr);
    cout << "main thread join thread_1" << endl;
    pthread_join(tid2, nullptr);
    cout << "main thread join thread_2" << endl;
    pthread_join(tid3, nullptr);
    cout << "main thread join thread_3" << endl;
    pthread_join(tid4, nullptr);
    cout << "main thread join thread_4" << endl;

    return 0;
}

// #include <iostream>
// #include <cstring>
// #include <string>
// #include <pthread.h>
// #include <unistd.h>
// using std::cout;
// using std::endl;
// using std::string;

// void printTid(const char* threadName, const pthread_t& tid) {
//     printf("%s is runing, tid: %lu, pid: %d\n", threadName, tid, getpid());
// }

// void* startRoutine(void* args) {
//     // pthread_detach(pthread_self());
//     string name = (char*)args;
//     int cnt = 1;
//     while (cnt--) {
//         printTid(name.c_str(), pthread_self());
//         sleep(1);
//     }
//     printf("%s is over\n", name.c_str());

//     return nullptr;
// }

// int main() {
//     pthread_t tid1, tid2, tid3, tid4;

//     pthread_create(&tid1, nullptr, startRoutine, (void*)"thread_1");

//     pthread_detach(tid1);
//     cout << "main thread detach thread_1" << endl;

//     // pthread_create(&tid2, nullptr, startRoutine, (void*)"thread_2");
//     // pthread_create(&tid3, nullptr, startRoutine, (void*)"thread_3");
//     // pthread_create(&tid4, nullptr, startRoutine, (void*)"thread_4");

//     // sleep(2);

//     // while (true) {
//     //     printTid("main thread", pthread_self());
//     //     sleep(1);
//     // }

//     int joinRet = pthread_join(tid1, nullptr);
//     cout << strerror(joinRet) << endl;
//     // joinRet = pthread_join(tid2, nullptr);
//     // cout << strerror(joinRet) << endl;
//     // joinRet = pthread_join(tid3, nullptr);
//     // cout << strerror(joinRet) << endl;
//     // joinRet = pthread_join(tid4, nullptr);
//     // cout << strerror(joinRet) << endl;
//     sleep(5);       // 防止主线程先退出

//     return 0;
// }

// #include <iostream>
// #include <string>
// #include <pthread.h>
// #include <unistd.h>
// using std::cout;
// using std::endl;
// using std::string;

// void printTid(const char* threadName, const pthread_t& tid) {
//     cout << threadName << " is runing, "
//          << "tid: " << tid << ", pid: " << getpid() << endl;
// }

// void* callBack1(void* args) {
//     char* threadName = (char*)args;
//     //pthread_t tid = (pthread_t)args;  // 这里如果想要向主线程发送取消请求, 则args需要是主线程的id
//     int cnt = 5;
//     while (true) {
//         printTid("thread_1", pthread_self());
//         //pthread_cancel(pthread_self());

//         sleep(1);
//         cnt--;
//         if (cnt == 0) {
//             // pthread_cancel(tid);                      // 新线程向主线程发送取消请求
//             pthread_cancel(pthread_self());            // 新线程向自己发送取消请求
//             // pthread_exit((void*)123);
//             //  int i = 1;
//             //  i /= 0;
//             // int* pi = nullptr;
//             //*pi = 123;
//         }
//     }
//     // cout << "thread_1 is over" << endl;

//     // int* ret = new int(123);
//     // return (void*)ret;
// }

// int main() {
//     pthread_t tid1;

//     PTHREAD_CANCELED;

//     pthread_create(&tid1, nullptr, callBack1, (void*)"thread_1");
//     // sleep(2);
//     // pthread_cancel(tid1);
//     // cout << "main thread cancel thread_1" << endl;

//     // while(true) {
//     //     printTid("main thread", pthread_self());
//     //     sleep(1);
//     // }

//     // sleep(10);

//     void* ret = nullptr;
//     pthread_join(tid1, &ret);
//     cout << "main thread join thread_1 , ready to print thread_1 ret" << endl;
//     sleep(2);
//     cout << "print thread_1 ret: " << (long long)ret << endl;

//     // sleep(15);  // 等15s，让thread_1运行完

//     // void* ret = nullptr;
//     // pthread_join(tid1, &ret);
//     // cout << "main thread join thread_1 , ready to print thread_1 ret" << endl;

//     // sleep(2);

//     // cout << "print thread_1 ret: " << *((int*)ret) << endl;
//     // delete (int*)ret;

//     // cout << "thread_1 id: " << tid1 << endl;

//     // while (true) {
//     //     cout << " 主线程运行: " << getpid() << " " << endl;
//     //     sleep(1);
//     // }

//     // void* ret = nullptr;
//     // pthread_join(tid1, &ret);

//     // cout << "main thread join thread_1 , ready to print thread_1 ret" << endl;

//     // sleep(2);
//     // cout << (char*)ret << endl;

//     return 0;
// }