#include "util.hpp"
#include "threadPool.hpp"
#include "task.hpp"
#include "daemonize.hpp"
#include "protocol.hpp"

// 保证不会出现除零和摸零的情况
std::map<char, std::function<int(int, int)>> opFunctions{
	{'+', [](int elemOne, int elemTwo) { return elemOne + elemTwo; }},
	{'-', [](int elemOne, int elemTwo) { return elemOne - elemTwo; }},
	{'*', [](int elemOne, int elemTwo) { return elemOne * elemTwo; }},
	{'/', [](int elemOne, int elemTwo) { return elemOne / elemTwo; }},
	{'%', [](int elemOne, int elemTwo) { return elemOne % elemTwo; }}};

static response calculator(const request& req) {
	response resp;

	int x = req.get_x();
	int y = req.get_y();
	int op = req.get_op();

	if (opFunctions.find(req.get_op()) == opFunctions.end()) {
		resp.set_exitCode(-3); // 非法操作符
	}
	else {
		if (y == 0 && op == '/') {
			resp.set_exitCode(-1); // 除零错误
		}
		else if (y == 0 && op == '%') {
			resp.set_exitCode(-2); // 模零错误
		}
		else {
			resp.set_result(opFunctions[op](x, y));
		}
	}

	return resp;
}

// 指定协议, 传输的数据 单个完整的结构化数据 转换成传输格式为: "strLen\r\n_x _op _y\r\n"
// strLen, 即用字符串表示有效载荷的实际长度; _x _op _y, 即为实际的有效载荷, 单个完整的传输数据 我们这里成为 strPackage
void netCal(int sock, const std::string& clientIp, uint16_t clientPort) {
	assert(sock >= 0);
	assert(!clientIp.empty());
	assert(clientPort >= 1024);

	std::string inBuffer;
	while (true) {
		request req;
		char buffer[128];
		ssize_t s = read(sock, buffer, sizeof(buffer) - 1);
		if (s == 0) {
			logMessage(NOTICE, "client[%s:%d] close socket, service done ...", clientIp.c_str(), clientPort);
			break;
		}
		else if (s < 0) {
			logMessage(WARINING, "read client[%s:%d] error, errorCode: %d, errorMessage: %s ", clientIp.c_str(), clientPort, errno, strerror(errno));
			break;
		}

		// 走到这里 读取成功
		// 但是, 读取到的内容是什么呢?
		// 本次读取, 有没有可能读取到的只是发送过来的一部分呢? 如果发送了一条或者多条完整strPackage, 却没有读取完整呢?
		// 这种情况是有可能发生的, 所以不能直接进行 decode 以及 反序列化, 需要先检查

		buffer[s] = '\0';
		inBuffer += buffer; // 将读取到的内容 += 在inBuffer后
		// 然后 根据inBuffer的内容, 检查是否已经接收到了一个完整的 strPackage
		uint32_t strPackageLen = 0;
		std::string package = decode(inBuffer, &strPackageLen);
		// TODO 这里decode 需要实现一些功能
		// 检验inBuffer中是否存在至少一个完整的strPackage, 如果存在则decode并返回decode之后的string, 并获取strPackage有效载荷长度 存储在strPackageLen中
		if (strPackageLen == 0)
			continue; // 说明 没有一个完整的strPackage

		// 走到这里 就获取了一个完整的strPackage并进行了decode, 获取了有效载荷存储到了 package 中
		// 就可以进行反序列化了
		if (req.deserialize(package)) {
			// 反序列化成功, 则进入
			// 处理计算
			response resp = calculator(req);

			std::string respPackage;
			resp.serialize(&respPackage); // 对响应resp序列化
			// 对报文 encode
			respPackage = encode(respPackage, respPackage.size());
			// TODO encode需要实现获取报文有效载荷长度, 并以字符串形式添加报头, 并将添加了抱头的字符串返回
			// 最后就可以响应写入
			write(sock, respPackage.c_str(), respPackage.size());
		}
	}
}

class tcpServer {
public:
	tcpServer(uint16_t port, const std::string& ip = "")
		: _port(port)
		, _ip(ip)
		, _listenSock(-1) {}

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

		// 线程池版本
		// 服务器初始化时, 要加载线程池
		_tP = threadPool<Task>::getInstance();
	}

	// 服务器初始化完成之后, 就可以启动了
	void loop() {
		//signal(SIGCHLD, SIG_IGN); // 忽略子进程推出信号, 子进程退出时就会自动回收

		// 线程池版本, 在服务器启动时, 也开启线程池
		_tP->start();
		logMessage(DEBUG, "threadPool start success, thread num: %d", _tP->getThreadNum());
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

			Task t(serviceSock, peerIP, peerPort, netCal);
			_tP->pushTask(t);
		}
	}

private:
	uint16_t _port; // 端口号
	std::string _ip;
	int _listenSock; // 服务器套接字文件描述符
	threadPool<Task>* _tP;
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

	daemonize(); // 守护进程

	log log;
	log.enable();
	tcpServer svr(port, ip);

	svr.init();
	svr.loop();

	return 0;
}
