#include "ringQueue.hpp"
#include <iostream>
#include <ctime>
#include <unistd.h>
using std::cout;

// 消费线程调用函数
void* consumer(void* args) {
    sleep(10);
    ringQueue<int>* ringQp = static_cast<ringQueue<int>*>(args);
    while (true) {
        sleep(1);
        int data = ringQp->pop();
        cout << "consumer_pthread[" << pthread_self() << "]"
             << " 消费了一个数据: " << data << endl;
    }
}

// 生产线程调用函数
void* productor(void* args) {
    ringQueue<int>* ringQp = static_cast<ringQueue<int>*>(args);
    while (true) {
        int data = rand() % 20;
        ringQp->push(data);
        cout << "productor_pthread[" << pthread_self() << "]"
             << " 生产了一个数据: " << data << endl;
        usleep(500000);
    }
}

int main() {
    srand((unsigned long)time(nullptr) ^ getpid());

    ringQueue<int> ringQ;

    pthread_t con1, con2, con3, pro1, pro2, pro3;
    pthread_create(&con1, nullptr, consumer, &ringQ);
    pthread_create(&con2, nullptr, consumer, &ringQ);
    pthread_create(&con3, nullptr, consumer, &ringQ);
    pthread_create(&pro1, nullptr, productor, &ringQ);
    pthread_create(&pro2, nullptr, productor, &ringQ);
    pthread_create(&pro3, nullptr, productor, &ringQ);

    pthread_join(con1, nullptr);
    pthread_join(con2, nullptr);
    pthread_join(con3, nullptr);
    pthread_join(pro1, nullptr);
    pthread_join(pro2, nullptr);
    pthread_join(pro3, nullptr);

    return 0;
}