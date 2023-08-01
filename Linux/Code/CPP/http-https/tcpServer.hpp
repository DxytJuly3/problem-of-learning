#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "logMessage.hpp"

#define SOCKET_ERR 1
#define BIND_ERR 2
#define LISTEN_ERR 3
#define USE_ERR 4
#define CONNECT_ERR 5
#define FORK_ERR 6
#define WAIT_ERR 7

#define CRLF "\r\n"
#define SPACE " "
#define SPACE_LEN strlen(SPACE)
#define HOME_PAGE "index.html"
#define ROOT_PATH "wwwRoot"

std::string getPath(std::string httpRequest) {
	// 要从请求的第一行获取资源路径
	// 所以要先找到请求的第一个`\r\n`
	std::size_t pos = httpRequest.find(CRLF);
	if (pos == std::string::npos) {
		return "";
	}
	// 找到第一行结尾之后, 就可以获取第一行的内容了
	std::string requestFirstLine = httpRequest.substr(0, pos);
	// 获取第一行的内容之后, 取两个空格, 空格之间的内容即为路径
	std::size_t firstSpacePos = requestFirstLine.find_first_of(SPACE);
	if (firstSpacePos == std::string::npos) {
		return "";
	}
	std::size_t secondSpacePos = requestFirstLine.find_last_of(SPACE);
	if (secondSpacePos == std::string::npos) {
		return "";
	}

	std::string path = requestFirstLine.substr(firstSpacePos + SPACE_LEN, secondSpacePos - (firstSpacePos + SPACE_LEN));

	// 如果请求的只有一个 / 那也肯定不能把 web根目录下的所有文件都响应回去
	// 当请求的文件路径是 / 时, 就将主页响应回去 一般为 index.html
	if (path.size() == 1 && path[0] == '/') {
		path += HOME_PAGE;
	}

	return path;
}

std::string readFile(const std::string& recource) {
	std::ifstream in(recource, std::ifstream::binary);
	if (!in.is_open())
		return "404";

	std::vector<char> buffer(std::istreambuf_iterator<char>(in), {});
	in.close();

	std::string fileContent(buffer.begin(), buffer.end());

	return fileContent;
}

void handlerHttpRequest(int sock) {
	char buffer[1024];
	ssize_t s = read(sock, buffer, sizeof buffer - 1);
	if (s > 0) {
		std::cout << buffer << std::endl;
	}

	// 获取文件路径
	std::string path = getPath(buffer);
	std::string recource;
	recource += ROOT_PATH;
	recource += path;

	// 获取文件内容
	std::string fileContent = readFile(recource);

	std::string response;
	// 响应行
	response += "HTTP/1.1 200 OK\r\n";
	// response += "HTTP/1.1 302 Moved Temporarily\r\n";
	// response += "Location: https://www.baidu.com\r\n";
	response += "Set-Cookie: This is a cookie\r\n";
	response += ("Content-Length: " + std::to_string(fileContent.size()) + "\r\n");
	response += "\r\n";

	response += fileContent;

	send(sock, response.c_str(), response.size(), 0);
}

class tcpServer {
public:
	tcpServer(uint16_t port, const std::string& ip = "")
		: _port(port)
		, _ip(ip)
		, _listenSock(-1) {}

	~tcpServer() {
		if (_listenSock >= 0)
			close(_listenSock);
	}

	void init() {
		// 先创建套接字文件描述符
		_listenSock = socket(AF_INET, SOCK_STREAM, 0);

		if (_listenSock < 0) {
			logMessage(FATAL, "socket() faild:: %s : %d", strerror(errno), _listenSock);
			exit(SOCKET_ERR); // 创建套接字失败 以 SOCKET_ERR 退出
		}
		logMessage(DEBUG, "socket create success: %d", _listenSock);

		struct sockaddr_in local;
		std::memset(&local, 0, sizeof(local));

		// 填充网络信息
		local.sin_family = AF_INET;
		local.sin_port = htons(_port);
		_ip.empty() ? (local.sin_addr.s_addr = htonl(INADDR_ANY))
					: (inet_aton(_ip.c_str(), &local.sin_addr));

		// 绑定网络信息到主机
		if (bind(_listenSock, (const struct sockaddr*)&local, sizeof(local)) == -1) {
			// 绑定失败
			logMessage(FATAL, "bind() faild:: %s : %d", strerror(errno), _listenSock);
			exit(BIND_ERR);
		}
		logMessage(DEBUG, "socket bind success : %d", _listenSock);
		// 监听是否有其他主机发来连接请求, 需要用到接口 listen()
		if (listen(_listenSock, 5) == -1) {
			logMessage(FATAL, "listen() faild:: %s : %d", strerror(errno), _listenSock);
			exit(LISTEN_ERR);
		}
		logMessage(DEBUG, "listen success : %d", _listenSock);
	}

	// 服务器初始化完成之后, 就可以启动了
	void loop() {
		while (true) {
			struct sockaddr_in peer;		  // 输出型参数 接受所连接主机客户端网络信息
			socklen_t peerLen = sizeof(peer); // 输入输出型参数

			// 使用 accept() 接口, 接受来自其他网络客户端的连接
			int serviceSock = accept(_listenSock, (struct sockaddr*)&peer, &peerLen);
			if (serviceSock == -1) {
				logMessage(WARINING, "accept() faild:: %s : %d", strerror(errno), serviceSock);
				continue;
			}
			// 连接成功之后, 就可以获取到连接客户端的网络信息了:
			uint16_t peerPort = ntohs(peer.sin_port);
			std::string peerIP = inet_ntoa(peer.sin_addr);
			logMessage(DEBUG, "accept success: [%s: %d] | %d ", peerIP.c_str(), peerPort, serviceSock);

			pid_t id = fork();
			if (id == 0) {
				close(_listenSock);

				if (fork() > 0)
					exit(0);

				handlerHttpRequest(serviceSock);
				exit(0);
			}
			waitpid(id, nullptr, 0);

			close(serviceSock);
		}
	}

private:
	uint16_t _port; // 端口号
	std::string _ip;
	int _listenSock; // 服务器套接字文件描述符
};
