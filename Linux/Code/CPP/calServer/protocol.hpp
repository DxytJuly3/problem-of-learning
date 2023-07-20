#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <cstring>

#define CRLF "\r\n"
#define CRLF_LEN strlen(CRLF)
#define SPACE " "
#define SPACE_LEN strlen(SPACE)

#define OPS "+-*/%"

#define BUFFER_SIZE 1024

std::string encode(const std::string& inS, uint32_t len) {
	std::string encodeIn = std::to_string(len); // len
	encodeIn += CRLF; // len\r\n 
	encodeIn += inS; // len\r\ninS
	encodeIn += CRLF; // len\r\n\inS\r\n

	return encodeIn;
}

// strPackage: 长度字段\r\n有效载荷\r\n
std::string decode(std::string& inS, uint32_t* len) {
	assert(len);

	*len = 0;
	// 1. 确认inBuffer存在 "\r\n"
	size_t pos = inS.find(CRLF);
	if (pos == std::string::npos) {
		// 没有找到"\r\n" 表示没有一个完整的表示有效载荷长度的字段
		// 即 strPackage 不完整
		return "";
	}

	// 2. 获取长度
	// 已经获取了第一个"\r\n"位置, 前面即为长度字段
	std::string inLen = inS.substr(0, pos);
	int intLen = atoi(inLen.c_str());

	// 3. 确认有效载荷完整
	// 已经获取了有效载荷的长度, 就可以判断有效载荷是否完整了
	int surplus = inS.size() - 2 * CRLF_LEN - pos; // 计算inBuffer中 减去长度字段的长度 再减去两个"\r\n", 得到inBuffer的剩余长度
	if (surplus < intLen) {
		// inBuffer剩余长度小于长度字段所记录的长度, 表示有效载荷不完整
		return "";
	}

	// 4. 获取有效载荷
	// pos 是第一个"\r\n"的位置, 之后就是有效载荷的位置
	std::string package = inS.substr(pos + CRLF_LEN, intLen);
	*len = intLen;

	// 5. 将完整的strPackage从inBuffer中剔除
	int removeLen = inLen.size() + 2 * CRLF_LEN + intLen; // 需要剔除的长度为 长度字段的长度 有效载荷的长度 以及 2个"\r\n"的长度
	inS.erase(0, removeLen);							  // std::string::erase() 第二个参数表示要删除的字符长度

	return package;
}

// 定制请求的协议
class request {
public:
	request() {}
	~request() {}

	void serialize(std::string* out) {
	}

	// 反序列化 -- 字符串 -> 结构化的数据
	bool deserialize(const std::string& in) {
		// in 的格式 1 + 1
		// 先查找两个空格的位置
		size_t posSpaceOne = in.find(SPACE);
		if (posSpaceOne == std::string::npos)
			return false;
		size_t posSpaceTwo = in.rfind(SPACE);
		if (posSpaceTwo == std::string::npos)
			return false;

		// 再获取三段字符串
		std::string dataOne = in.substr(0, posSpaceOne);
		std::string dataTwo = in.substr(posSpaceTwo + SPACE_LEN, std::string::npos);
		std::string oper = in.substr(posSpaceOne + SPACE_LEN, posSpaceTwo - (posSpaceOne + SPACE_LEN));
		if(oper.size() != 1)
			return false;	// 操作符不是一位

		_x = atoi(dataOne.c_str());
		_y = atoi(dataTwo.c_str());
		_op = oper[0];

		return true;
	}

	int get_x() const {
		return _x;
	}
	int get_y() const {
		return _y;
	}
	char get_op() const {
		return _op;
	}
	void set_x(int x) {
		_x = x;
	}
	void set_y(int y) {
		_y = y;
	}
	void set_op(char op) {
		_op = op;
	}

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

	void serialize(std::string* out) {
		std::string exitCode = std::to_string(_exitCode);
		std::string result = std::to_string(_result);

		*out = exitCode;
		*out += SPACE;
		*out += result;
	}

	bool deserialize(const std::string& in) {
		return true;
	}
	void set_exitCode(int exitCode) {
		_exitCode = exitCode;
	}
	void set_result(int result) {
		_result = result;
	}
	int get_exitCode() const {
		return _exitCode;
	}
	int get_result() const {
		return _result;
	}

private:
	int _exitCode;
	int _result;
};

bool makeRequest(const std::string& message, request* req) {
	char strtmp[BUFFER_SIZE];
    snprintf(strtmp, sizeof strtmp, "%s", message.c_str());
    char *left = strtok(strtmp, OPS);
    if (!left)
        return false;
    char *right = strtok(nullptr, OPS);
    if (!right)
        return false;
    char mid = message[strlen(left)];

	req->set_x(atoi(left));
	req->set_y(atoi(right));
	req->set_op(mid);

    return true;
}
