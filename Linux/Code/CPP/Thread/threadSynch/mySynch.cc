#include <iostream>
#include <unistd.h>
#include <pthread.h>
using std::cin;
using std::cout;
using std::endl;

// 定义并初始化全局互斥锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 定义全局条件变量
pthread_cond_t cond;

// // 定义一个全局退出变量, 用于判断条件
volatile bool quit = false;

void* waitCommand(void* args) {
    // pthread_detach(pthread_self()); // 先让线程自己分离自己, 我们就不在主线程中回收线程了
    // 在此例中, 如果不分离, 线程回收会是个问题. 但具体问题后面再解释和解决.
    // 这里我们只是展示一下 接口的最基本的用法和现象
    const char* name = (const char*)args;

    while (!quit) {
        //  不满足退出条件, 就进来等待
        pthread_cond_wait(&cond, &mutex);
        cout << name << ", tid: " << pthread_self() << ", run……" << endl;
    }
    // pthread_mutex_unlock(&mutex);       // 暂时不解释 这里解锁的原因
    // usleep(100);
    cout << name << ", tid: " << pthread_self() << ", end……" << endl;

    return nullptr;
}

int main() {
    pthread_cond_init(&cond, nullptr);

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, nullptr, waitCommand, (void*)"Thread_1");
    pthread_create(&tid2, nullptr, waitCommand, (void*)"Thread_2");
    pthread_create(&tid3, nullptr, waitCommand, (void*)"Thread_3");
    while (true) {
        char c = 'a';
        cout << "请输入你的命令(N/Q):: ";
        cin >> c;
        if (c == 'N' | c == 'n') {
            // pthread_cond_signal(&cond);
            pthread_cond_broadcast(&cond);
        }
        else {
            quit = true;
            pthread_cond_broadcast(&cond);
            break;
        }
        usleep(1000);       // 让主线程usleep一下, 防止线程之间在屏幕上打印干扰
    }

    pthread_join(tid1, nullptr);
    pthread_join(tid2, nullptr);
    pthread_join(tid3, nullptr);

    pthread_cond_destroy(&cond);

    return 0;
}

// // 用来存储函数
// typedef void (*func)();
// vector<func> funcs;

// void show() {
//     cout << "Hello Show" << endl;
// }

// void print() {
//     cout << "Hello Print" << endl;
// }
