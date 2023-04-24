#pragma once
#include <iostream>
#include <vector>
#include <semaphore.h>
using std::cout;
using std::endl;
using std::vector;

const int gDefultCap = 30; 

template <class T>
class ringQueue {
public:
    // 构造函数
    ringQueue(const int cap = gDefultCap) 
        : _ringQueue(cap) 
        , _pIndex(0)
        , _cIndex(0) {
        sem_init(&_roomSem, 0, _ringQueue.size());
        sem_init(&_dataSem, 0, 0);
        // sem_init() 接口的 
        // 第一个参数是 需要初始化的信号量, 
        // 第二个参数是 
        // 第三个参数是 需要初始化为多少

        // 初始化锁
        pthread_mutex_init(&_pMutex, nullptr);
        pthread_mutex_init(&_cMutex, nullptr);
    }
    // 析构函数
    ~ringQueue() {
        sem_destroy(&_roomSem);
        sem_destroy(&_dataSem);

        pthread_mutex_destroy(&_pMutex);
        pthread_mutex_destroy(&_cMutex);
    }
    // 生产接口
    void push(const T &in) {
        // 生产数据
        // 先申请空间信号量
        sem_wait(&_roomSem);                // 申请成功则 _roomSem--, 否则等待
        pthread_mutex_lock(&_pMutex);       // 申请信号量成功后, 加锁
        _ringQueue[_pIndex] = in;           // 将数据放入 数组
        _pIndex++;                          // 生产者下一次生产数据的位置 ++
        _pIndex %= _ringQueue.size();       // 跟新下标, 保证环形特性
        pthread_mutex_unlock(&_pMutex);     // 访问完临界资源, 解锁
        sem_post(&_dataSem);                // 数组中数据+1, 那么 dataSem 需要++
    }
    // 消费接口
    T pop() {
        // 消费数据
        // 先申请数据信号量
        sem_wait(&_dataSem);            // 申请成功则 _dataSem--, 否则等待
        pthread_mutex_lock(&_cMutex);
        T tmp = _ringQueue[_cIndex];    // 存储应拿到的数据
        _cIndex++;
        _cIndex %= _ringQueue.size();
        pthread_mutex_unlock(&_cMutex);
        sem_post(&_roomSem); // 拿出了数据, 空间+1, 那么 _roomSem ++
        return tmp;
    }


private:
    vector<T> _ringQueue;   // 模拟循环队列的数组
    sem_t _roomSem;         // 空间资源信号量, 生产者申请
    sem_t _dataSem;         // 数据资源信号量, 消费者申请
    uint32_t _pIndex;       // 生产者生产数据的索引下标, 即插入数据的下标
    uint32_t _cIndex;       // 消费者消费数据的索引下标, 即获取数据的下标

    // 保护索引下标的锁
    pthread_mutex_t _cMutex;    // 消费数据索引下标的锁
    pthread_mutex_t _pMutex;    // 生产数据索引下标的锁
};