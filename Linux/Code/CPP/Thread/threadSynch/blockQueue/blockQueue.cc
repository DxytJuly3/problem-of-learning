#include <iostream>
#include <ctime>
#include "blockQueue.hpp"
#include "Task.hpp"
using std::cout;
using std::endl;

const std::string ops = "+-*/%";

// 生产任务接口
// void* productor(void* args) {
//     blockQueue<Task>* pBq = static_cast<blockQueue<Task>*>(args);
//     while (true) {
//         // 制作任务
//         int elemOne = rand() % 50;
//         int elemTwo = rand() % 10;
//         char oper = ops[rand() % 4];        // 操作符
//         Task t(elemOne, elemTwo, oper);
//         // 生产任务
//         pBq->push(t);
//         cout << "producter[" << pthread_self() << "] " <<
//             (unsigned long)time(nullptr) << " 生产了一个任务: " <<
//             elemOne << oper << elemTwo << "=?" << endl;
//         sleep(1);
//     }

//     return nullptr;
// }

// void* consumer(void* args) {
//     blockQueue<Task>* pBq = static_cast<blockQueue<Task>*>(args);
//     while (true) {
//         // 消费任务
//         Task t = pBq->pop();
//         // 处理任务
//         int result = t();
//         int elemOne, elemTwo;
//         char oper;
//         t.get(&elemOne, &elemTwo, &oper);
//         cout << "consumer[" << pthread_self() << "] " <<
//             (unsigned long)time(nullptr) << " 消费了一个任务: " <<
//             elemOne << oper << elemTwo << "=" << result << endl;
//     }

//     return nullptr;
// }

void* productor(void* args) {
    blockQueue<int>* pBq = static_cast<blockQueue<int>*>(args);
    while (true) {
        // 制作数据
        int data = rand() % 10;
        // 向队列中生产数据
        pBq->push(data);
        cout << "productor 生产数据完成……" << data << endl;
        sleep(1);
    }

    return nullptr;
}

void* consumer(void* args) {
    blockQueue<int>* pBq = static_cast<blockQueue<int>*>(args);
    while (true) {
        sleep(10);
        int data = pBq->pop();
        cout << "consumer 消费数据完成……" << data << endl;
    }

    return nullptr;
}

int main() {
    // 设置一个随机数种子
    srand((unsigned long)time(nullptr) ^ getpid());
    // 定义阻塞队列
    // 创建两个线程

    blockQueue<int> bq;
    // blockQueue<Task> bq;

    pthread_t pro, con;
    pthread_create(&pro, nullptr, productor, &bq); // 生产线程
    pthread_create(&con, nullptr, consumer, &bq);  // 消费线程

    pthread_join(pro, nullptr);
    pthread_join(con, nullptr);

    return 0;
}