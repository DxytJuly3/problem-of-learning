#pragma once

#include <iostream>
#include <cassert>
#include <string>

std::string encode(std::string& inS, uint32_t len) {
}

std::string decode(std::string& inS, uint32_t* len) {
}

// 定制请求的协议
class request {
public:
	request() {}
	~request() {}

private:
	int _x;
	int _y;
	char _op;
};

// 定制响应的协议
class response {
public:
	response()
		: _exitCode(0)
		, _result(0) {}
	~response() {}

private:
	int _exitCode;
	int _result;
};
