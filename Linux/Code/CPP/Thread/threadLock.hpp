#pragma once
#include <iostream>
#include <pthread.h>
using std::cout;
using std::endl;

class myMutex {
public:
    myMutex() {
        pthread_mutex_init(&_lock, nullptr);
    }
    void lock() {
        pthread_mutex_lock(&_lock);
    }
    void unlock() {
        pthread_mutex_unlock(&_lock);
    }
    ~myMutex() {
        pthread_mutex_destroy(&_lock);
    }

private:
    pthread_mutex_t _lock;
};

// 锁—警卫
class lockGuard {
public:
    lockGuard(myMutex* myMutex)
        : _myMutex(myMutex) {
        _myMutex->lock();
        printf("上锁成功……\n");
    }
    ~lockGuard() {
        _myMutex->unlock();
        printf("解锁成功……\n");
    }

private:
    myMutex* _myMutex;
};