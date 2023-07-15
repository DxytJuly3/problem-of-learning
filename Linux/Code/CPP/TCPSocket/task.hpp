#pragma once

#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <pthread.h>
#include <unistd.h>
#include "logMessage.hpp"

// 此例中的任务, 是tcp服务器与客户端通信
// 需要知道 客户端的网络信息, 还需要知道线程需要执行的功能函数
// 因为 此任务是在线程池中让线程执行的. 会在线程的回调函数中 通过此任务类调用, 所以此类还需要知道功能函数
class Task {
public:
	// 包装器 将功能函数包装起来 函数类型: void 函数名(int sock, std::string ip, uint16_t port)
	using callback_t = std::function<void(int, std::string, uint16_t)>;

	Task()
		: _sock(-1)
		, _port(-1) {}

	Task(int sock, std::string ip, uint16_t port, callback_t func)
		: _sock(sock)
		, _ip(ip)
		, _port(port)
		, _func(func) {}

	// 仿函数
	void operator()() {
		logMessage(DEBUG, "线程[%p] 处理 %s:%d 请求 ---开始", pthread_self(), _ip.c_str(), _port);

		_func(_sock, _ip, _port);

		logMessage(DEBUG, "线程[%p] 处理 %s:%d 请求 ---结束", pthread_self(), _ip.c_str(), _port);
	}

	void run() {
		(*this)();
	}

private:
	int _sock;		  // 与客户端通信的套接字
	std::string _ip;  // 客户端IP
	uint16_t _port;	  // 客户端端口号
	callback_t _func; // 功能回调函数
};
