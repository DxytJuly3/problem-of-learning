#pragma once

#include <iostream>
#include <ostream>
#include <queue>
#include <cassert>
#include <pthread.h>
#include <unistd.h>

size_t gThreadNum = 5;

template <class T>
class threadPool {
public:
	threadPool(size_t threadNum = gThreadNum)
		: _threadNum(threadNum)
		, _isStart(false) {
		assert(_threadNum > 0);

		pthread_mutex_init(&_mutex, nullptr); // 初始化 锁
		pthread_cond_init(&_cond, nullptr);	  // 初始化 条件变量
	}
	// 线程回调函数
	// static 修饰, 是因为需要让函数参数 取消this指针, 只留一个void*
	// 但是由于 需要访问类内成员, 所以 传参需要传入this指针
	static void* threadRoutine(void* args) {
		// 线程执行回调函数
		// 先分离, 自动回收
		pthread_detach(pthread_self());

		// 获取this指针
		threadPool<T>* tP = static_cast<threadPool<T>*>(args);
		while (true) {
			// 即将通过任务队列给线程分配任务, 即 多线程访问临界资源, 需要上锁
			tP->lockQueue();
			while (!tP->haveTask()) {
				// 任务队列中没有任务, 就让线程通过条件变量等待
				tP->waitForTask();
			}
			// 走到这里 说明条件队列中有任务
			// 线程已经可以获取到任务
			T task = tP->popTask();
			// 获取到任务之后 临界资源的访问就结束了, 可以释放锁了.
			// 尽量避免拿着锁 执行任务
			tP->unlockQueue();

			// 为任务类提供一个运行的接口, 这样获取到任务之后 直接 task.run();
			task.run();
		}
	}

	// 开启线程池
	void start() {
		try {
			// _isStart 为true 则说明线程池已经开启
			if (_isStart)
				throw "Error: thread pool already exists";
		}
		catch (const char* e) {
			std::cout << e << std::endl;
			return;
		}

		for (int i = 0; i < _threadNum; i++) {
			pthread_t temp;
			pthread_create(&temp, nullptr, threadRoutine, this); // 回调函数的参数传入this指针, 用于类访问内成员
		}
		// 开启线程池之后, 要把 _isStart 属性设置为 true
		_isStart = true;
	}

	// 给任务队列添加任务 并分配任务
	void pushTask(const T& in) {
		// 上锁
		lockQueue();
		_taskQueue.push(in);
		// 任务队列中已经存在任务, 线程就不用再等待了, 就可以唤醒线程
		choiceThreadForHandler();
		// 释放锁
		unlockQueue();
	}

	~threadPool() {
		pthread_mutex_destroy(&_mutex);
		pthread_cond_destroy(&_cond);
	}

private:
	// 线程调度 即为从任务队列中给各线程分配任务
	// 所以 任务队列是临界资源需要上锁
	void lockQueue() {
		pthread_mutex_lock(&_mutex);
	}
	void unlockQueue() {
		pthread_mutex_unlock(&_mutex);
	}

	// 条件变量 使用条件, 判断是否任务队列是否存在任务
	bool haveTask() {
		return !_taskQueue.empty();
	}
	// 线程通过条件变量等待任务
	void waitForTask() {
		pthread_cond_wait(&_cond, &_mutex);
	}

	// 从任务队列中获取任务, 并返回
	T popTask() {
		T task = _taskQueue.front();
		_taskQueue.pop();

		return task;
	}

	// 唤醒在条件变量前等待的线程
	// 由于唤醒之后就是线程调度的过程
	// 所以函数名 是线程调度相关
	void choiceThreadForHandler() {
		pthread_cond_signal(&_cond);
	}

private:
	size_t _threadNum;		  // 线程池内线程数量
	bool _isStart;			  // 判断线程池是否已经开启
	std::queue<T> _taskQueue; // 任务队列
	pthread_mutex_t _mutex; // 锁 给临界资源使用 即任务队列 保证线程调度互斥
	pthread_cond_t _cond; // 条件变量 保证线程调度同步
};
