#pragma once

#include <cstdio>
#include <ctime>
#include <cstdarg>
#include <cassert>
#include <cstring>
#include <cerrno>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 宏定义 四个日志等级
#define DEBUG 0
#define NOTICE 1
#define WARINING 2
#define FATAL 3

#define LOGFILEPATH "serverLog.log"

const char* log_level[] = {"DEBUG", "NOTICE", "WARINING", "FATAL"};

class log {
public:
	log()
		: _logFd(-1) {}

	void enable() {
		umask(0);

		_logFd = open(LOGFILEPATH, O_WRONLY | O_CREAT | O_APPEND, 0666);
		assert(_logFd != -1);
		dup2(_logFd, STDOUT_FILENO);
		dup2(_logFd, STDERR_FILENO);
	}

	~log() {
		if (_logFd != -1) {
			// 将系统缓冲区内容刷入文件
			fsync(_logFd);
			close(_logFd);
		}
	}

private:
	int _logFd;
};

// 实现一个 可以输出: 日志等级、日志时间、用户、以及相关日志内容的 日志消息打印接口
void logMessage(int level, const char* format, ...) {
	// 通过可变参数实现, 传入日志等级, 日志内容格式, 日志内容相关参数

	// 确保日志等级正确
	assert(level >= DEBUG);
	assert(level <= FATAL);

	// 获取当前用户名
	char* name = getenv("USER");

	// 简单的定义log缓冲区
	char logInfo[1024];

	// 定义一个指向可变参数列表的指针
	va_list ap;
	// 将 ap 指向可变参数列表中的第一个参数, 即 format 之后的第一个参数
	va_start(ap, format);

	// 此函数 会通过 ap 遍历可变参数列表, 然后根据 format 字符串指定的格式, 将ap当前指向的参数以字符串的形式 写入到logInfo缓冲区中
	vsnprintf(logInfo, sizeof(logInfo) - 1, format, ap);

	// ap 使用完之后, 再将 ap置空
	va_end(ap); // ap = NULL

	// 通过判断日志等级, 来选择是标准输出流还是标准错误流
	FILE* out = (level == FATAL) ? stderr : stdout;

	// 获取本地时间
	time_t tm = time(nullptr);
	struct tm* localTm = localtime(&tm);
	char* localTmStr = asctime(localTm);
	char* nC = strstr(localTmStr, "\n");
	if (nC) {
		*nC = '\0';
	}
	fprintf(out, "%s | %s | %s | %s\n",
			log_level[level],
			localTmStr,
			name == nullptr ? "unknow" : name,
			logInfo);

	// 将C缓冲区的内容 刷入系统
	fflush(out);
	// 将系统缓冲区的内容 刷入文件
	fsync(fileno(out));
}
