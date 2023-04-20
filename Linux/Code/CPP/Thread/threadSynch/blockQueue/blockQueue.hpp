#pragma once
#include <iostream>
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
using std::queue;
using std::cout;
using std::endl;

const uint32_t gDefultCap = 5;

template <class T>
class blockQueue {
public:
    // 构造函数
    blockQueue(uint32_t cap  = gDefultCap) 
        :_cap(cap) {
        pthread_mutex_init(&_mutex, nullptr);           // 初始化锁
        pthread_cond_init(&_proCond, nullptr);          // 初始化生产线程使用的条件变量
        pthread_cond_init(&_conCond, nullptr);          // 初始化消费线程使用的条件变量
    }
    // 析构函数
    ~blockQueue() {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_conCond);
        pthread_cond_destroy(&_proCond);
    }
    // 生产接口
    void push(const T &in) {
        // 生产的全过程为
        // 1. 上锁
        // 2. 判满. 满不生产 条件等待, 不满则生产.
        // 3. 生产之后, 解锁
        // 4. 唤醒消费接口

        lockQueue();        // 上锁
        // 之保持最新的五个任务
        if(isFull()) {
            popCore();
        }
        // 条件等待
        // while(isFull()) {
        //     // 满 进入条件等待
        //     condWait(_proCond);        // 传入生产线程所用的条件变量, 让生产线程等待
        // }
        // 不满 则生产
        pushCore(in);
        // 解锁
        unlockQueue();
        condWakeUp(_conCond);          // 传入消费线程所用的条件变量, 唤醒消费线程
    }

    T pop() {
        // 消费的全过程为
        // 1. 上锁
        // 2. 判空. 空则不消费 条件等待, 不空 则消费
        // 3. 消费之后, 解锁
        // 4. 唤醒生产接口

        lockQueue();
        while(isEmpty()) {
            condWait(_conCond);
        }
        T tmp = popCore();
        unlockQueue();
        condWakeUp(_proCond);

        return tmp;
    }

    int size() {
        return _bq.size();
    }

private:
    // 队列上锁
    void lockQueue() {
        pthread_mutex_lock(&_mutex);
    }
    // 队列解锁
    void unlockQueue() {
        pthread_mutex_unlock(&_mutex);
    }
    // 判空
    bool isEmpty() {
        return _bq.empty();
    }
    // 判满
    bool isFull() {
        return _bq.size() == _cap;
    }
    // 条件等待
    void condWait(pthread_cond_t &cond) {
        pthread_cond_wait(&cond, &_mutex);
    }
    // 唤醒等待
    void condWakeUp(pthread_cond_t &cond) {
        pthread_cond_signal(&cond);
    }
    // 生产任务
    void pushCore(const T &in) {
        // 即为向队列中添加任务
        _bq.push(in);
    }
    // 消费任务
    T popCore() {
        // 即从队列中拿出任务
        T tmp = _bq.front();
        _bq.pop();
        return tmp;
    }

private:
    uint32_t _cap;                  // 队列容量
    queue<T> _bq;                   // 阻塞队列
    pthread_mutex_t _mutex;         // 互斥锁
    pthread_cond_t _conCond;        // 消费线程使用的条件变量
    pthread_cond_t _proCond;        // 生产线程使用的条件变量
};