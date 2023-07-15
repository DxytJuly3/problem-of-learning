#include "util.hpp"
#include "threadPool.hpp"
#include "task.hpp"

// 线程池版本, tcpServer无需创建线程
//class tcpServer;
//
//struct threadData {
//	threadData(uint16_t clientPort, std::string clientIP, int sock, tcpServer* ts)
//		: _clientPort(clientPort)
//		, _clientIP(clientIP)
//		, _sock(sock)
//		, _this(ts) {}
//
//	uint16_t _clientPort;
//	std::string _clientIP;
//	int _sock;
//	tcpServer* _this;
//};

class tcpServer {
public:
	tcpServer(uint16_t port, const std::string& ip = "")
		: _port(port)
		, _ip(ip)
		, _listenSock(-1) {}

//	static void* threadRoutine(void* args) {
//		// 线程分离
//		pthread_detach(pthread_self());
//
//		threadData* tD = static_cast<threadData*>(args);
//		tD->_this->low2upService(tD->_sock, tD->_clientIP, tD->_clientPort);
//
//		// 线程执行任务结束后, 需要delete掉 tD
//		// 不能在主线程 delete 因为, 线程还没有使用
//		delete tD;
//
//		return nullptr;
//	}

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

			// 连接到客户端之后, 就可以执行功能了
			// 执行转换功能 小写转大写

			// 此为单进程版本
			// 单进程版 连接多个客户端会出问题
			// 为什么呢?
			// 当一个客户端连接到服务器之后, 会调用low2upService()这个函数
			// 这个函数的主体是什么? 是一个死循环.
			// 单进程调用函数进入一个死循环, 就出不来了!
			// 后面的客户端在连接进来, 服务器是没办法响应的, 因为进程在一个死循环内执行呢
			// 要解决这个问题, 还需要多进程或者多线程的版本
			//low2upService(serviceSock, peerIP, peerPort);

			// 多进程v1
			//	pid_t id = fork();
			//	if (id == -1) {
			//		logMessage(FATAL, "Server fork() faild: %s", strerror(errno));
			//		exit(FORK_ERR);
			//	}
			//	else if (id == 0) {
			//		// 进入子进程
			//		// 子进程会继承 父进程的文件描述符表, 但是这已经是两个不同的进程了
			//		// 所以建议进入子进程之后, 先关闭_listenSock, 防止子进程代码可能对此文件造成影响
			//		close(_listenSock);
			//		low2upService(serviceSock, peerIP.c_str(), peerPort);
			//		exit(0);
			//	}
			//	// 这里是父进程执行的内容
			//	close(serviceSock);
			//	// 父进程需要手动关闭 连接客户端创建的与客户端通信的文件描述符
			//	// 如果不关闭父进程会发生文件描述符泄漏
			//	// 父子进程在各子进程中关闭某文件描述符 是不影响对方的

			// 多进程v2
			//	pid_t id = fork();
			//	if (id == -1) {
			//		logMessage(FATAL, "Server fork() faild: %s", strerror(errno));
			//		exit(FORK_ERR);
			//	}
			//	else if (id == 0) {
			//		// 子进程
			//		close(_listenSock);

			//		// 再创建子进程, 并且此进程退出
			//		if (fork() > 0) {
			//			exit(0);
			//		}
			//		// 这部分是再次创建的子进程 执行的, 也就是孙子进程, 因为父进程在创建出孙子进程时就推出了
			//		low2upService(serviceSock, peerIP.c_str(), peerPort);
			//		exit(0);
			//	}
			//	close(serviceSock);

			//	// 等待id子进程
			//	int ret = waitpid(id, nullptr, 0);
			//	// 就算是阻塞式的等待也无所谓, 因为 创建成功后马上就退出了
			//	if (ret == -1) {
			//		logMessage(FATAL, "Server waitpid() faild: %s", strerror(errno));
			//		exit(WAIT_ERR);
			//	}
			//	(void)ret;

			// 多线程版本
			// 让多线程执行low2upService(), 是需要传参的, 所以需要定义一个结构体, 存储可能使用到的参数
			//	threadData* tD = new threadData(peerPort, peerIP, serviceSock, this);
			//	pthread_t tid;
			//	pthread_create(&tid, nullptr, threadRoutine, (void*)tD);

			// 线程池版本
			// v1
			// 实现过线程池, 之后这里就很简单
			Task t(serviceSock, peerIP, peerPort, std::bind(&tcpServer::low2upService, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
			_tP->pushTask(t);
		}
	}

	void low2upService(int sock, const std::string& clientIP, const uint16_t& clientPort) {
		assert(sock > 0);
		assert(!clientIP.empty());

		// 一个用于存储来自客户端信息的数组
		char inbuffer[BUFFER_SIZE];
		while (true) {
			// TCP获取来自客户端的信息的操作就是 read
			// 从 服务器与客户端连接 的文件描述符中 读取来自客户端的信息
			// 可看作 通过文件描述符 从文件读取内容
			ssize_t s = read(sock, inbuffer, sizeof(inbuffer) - 1);
			if (s > 0) {
				// 大于零 就是读取到数据了
				inbuffer[s] = '\0';
				// 我们实现一个操作, 如果 客户端传输过来的信息是 quit 这个单词, 就表示客户端请求退出
				// 就可以退出 服务循环了
				if (strcasecmp(inbuffer, "quit") == 0) { // strcasecmp 忽略大小写比较
					logMessage(DEBUG, "Client requests to quit: [%s: %d]", clientIP.c_str(), clientPort);
					break;
				}
				// 走到这里 就可以进行小写转大写了
				logMessage(DEBUG, "low2up before: [%s: %d] >> %s", clientIP.c_str(), clientPort, inbuffer);
				for (int i = 0; i < s; i++) {
					if (isalpha(inbuffer[i]) && islower(inbuffer[i]))
						inbuffer[i] = toupper(inbuffer[i]);
				}
				logMessage(DEBUG, "low2up after: [%s: %d] >> %s", clientIP.c_str(), clientPort, inbuffer);

				// 上面做的都是对获取到的信息 进行转换
				// 最后需要做的就是 将转换后的信息 再重新回应给客户端
				// 而 回应给客户端 则是用 write, 可看做 通过文件描述符像文件写入内容
				write(sock, inbuffer, strlen(inbuffer));
			}
			else if (s == 0) {
				// s == 0, 表示什么?
				// 在管道通信中 read() 是阻塞式读取的. 此时 返回值为0, 表示管道的写入端关闭
				// 而 TCP类似, TCP中 read() 通常也是阻塞时读取的, 此时返回0, 表示客户端关闭
				// 所以此时, 该退出了
				logMessage(DEBUG, "Client has quited: [%s: %d]", clientIP.c_str(), clientPort);
				break;
			}
			else {
				// 到这里 本次 read() 出错
				logMessage(DEBUG, "Client [%s: %d] read:: %s", clientIP.c_str(), clientPort, strerror(errno));
				break;
			}
		}
		// 走到这里 循环已经退出了, 表示 client 也已经退出了
		// 所以 此时需要关闭文件描述符, 因为一个主机上的文件描述符数量是一定的, 达到上限之后 就无法再创建
		// 已经无用但没有被归还的文件描述符, 文件描述符泄漏
		close(sock);
		logMessage(DEBUG, "Service close %d sockFd", sock);
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

	tcpServer svr(port, ip);

	svr.init();
	svr.loop();

	return 0;
}
