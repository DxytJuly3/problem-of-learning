#include "logMessage.hpp"
#include "util.hpp"

class tcpServer {
public:
	tcpServer(uint16_t port, const std::string& ip = "")
		: _port(port)
		, _ip(ip) {}

	void init() {
		// 先创建套接字文件描述符
		// 不过, 与UDP不同的是 TCP是面向字节流的, 所以套接字数据类型 要使用 流式套接字
		_listenSock = socket(AF_INET, SOCK_STREAM, 0);

		if (_listenSock < 0) {
			// 套接字文件描述符创建失败
			logMessage(FATAL, "socket() faild:: %s : %d", strerror(errno), _listenSock);
			exit(SOCKET_ERR); // 创建套接字失败 以 SOCKET_ERR 退出
		}
		logMessage(DEBUG, "socket create success: %d", _listenSock);

		// 套接字创建成功, 就需要将向 sockaddr_in 里填充网络信息
		// 并将进程网络信息绑定到主机上
		struct sockaddr_in local;
		std::memset(&local, 0, sizeof(local));

		// 填充网络信息
		local.sin_family = AF_INET;
		local.sin_port = htons(_port);
		_ip.empty() ? (local.sin_addr.s_addr = htonl(INADDR_ANY)) : (inet_aton(_ip.c_str(), &local.sin_addr));

		// 绑定网络信息到主机
		if (bind(_listenSock, (const struct sockaddr*)&local, sizeof(local)) == -1) {
			// 绑定失败
			logMessage(FATAL, "bind() faild:: %s : %d", strerror(errno), _listenSock);
			exit(BIND_ERR);
		}
		logMessage(DEBUG, "socket bind success : %d", _listenSock);
		// 绑定了网络信息之后, 不同于 UDP, TCP是面向连接的.
		// 所以 在TCP服务器绑定了进程网络信息到内核中之后, 其他主机就有可能向服务器发送连接请求了
		// 然后, 所以 在绑定了网络信息之后, 要做的事就是 监听套接字
		// 监听是否有其他主机发来连接请求, 需要用到接口 listen()
		if (listen(_listenSock, 5) == -1) {
			logMessage(FATAL, "listen() faild:: %s : %d", strerror(errno), _listenSock);
			exit(LISTEN_ERR);
		}
		logMessage(DEBUG, "listen success : %d", _listenSock);
		// 开始监听之后, 别的主机就可以发送连接请求了.
	}

	// 服务器初始化完成之后, 就可以启动了
	void loop() {
		while (true) {
			struct sockaddr_in peer;		  // 输出型参数 接受所连接主机客户端网络信息
			socklen_t peerLen = sizeof(peer); // 输入输出型参数

			// 使用 accept() 接口, 接受来自其他网络客户端的连接
			// 成功会返回一个文件描述符, 失败则返回-1
			// 此函数是阻塞式的, 也就是说 在没有连接发送过来之前 进程会处于阻塞状态
			int serviceSock = accept(_listenSock, (struct sockaddr*)&peer, &peerLen);
			if (serviceSock == -1) {
				logMessage(WARINING, "accept() faild:: %s : %d", strerror(errno), serviceSock);
				continue;
			}
			// 走到这里, 就表示连接成功了
			// 连接成功之后, 就可以获取到连接客户端的网络信息了:
			uint16_t peerPort = ntohs(peer.sin_port);
			std::string peerIP = inet_ntoa(peer.sin_addr);
			logMessage(DEBUG, "accept success: [%s: %d] | %d ", peerIP.c_str(), peerPort, serviceSock);
		}
	}

private:
	uint16_t _port;	 // 端口号
	int _listenSock; // 服务器套接字文件描述符
	std::string _ip;
};

void Usage(std::string proc) {
	std::cerr << "Usage:: \n\t" << proc << " port ip" << std::endl;
	std::cerr << "example:: \n\t" << proc << " 8080 127.0.0.1" << std::endl;
}

int main(int argc, char* argv[]) {
	if (argc != 3 && argc != 2) {
		Usage(argv[0]);
		exit(USE_ERR);
	}
	uint16_t port = atoi(argv[1]);
	std::string ip;
	if (argc == 3) {
		ip = argv[2];
	}

	tcpServer svr(port, ip);

	svr.init();
	svr.loop();

	return 0;
}
