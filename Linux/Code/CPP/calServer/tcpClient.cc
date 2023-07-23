#include "util.hpp"
#include "protocol.hpp"

volatile bool quit = false;

void Usage(std::string proc) {
	std::cerr << "Usage:: \n\t" << proc << " serverIP serverPort" << std::endl;
	std::cerr << "example:: \n\t" << proc << " 127.0.0.1 8080" << std::endl;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		Usage(argv[0]);
		exit(USE_ERR);
	}
	std::string serverIP = argv[1];
	uint16_t serverPort = atoi(argv[2]);

	// 先创建套接字文件描述符
	int sockFd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockFd < 0) {
		// 套接字文件描述符创建失败
		logMessage(FATAL, "socket() faild:: %s : %d", strerror(errno), sockFd);
		exit(SOCKET_ERR); // 创建套接字失败 以 SOCKET_ERR 退出
	}
	logMessage(DEBUG, "socket create success: %d", sockFd);

	// 客户端创建套接字之后, 首先需要做什么?
	// 服务器创建套接字之后, 需要填充绑定网络信息, 客户端也需要, 但是与UDP相同 不需要手动填充 与 bind
	// 需要listen吗? 不需要, 因为客户端不会被主动连接
	// 需要accept吗? 不需要
	// 此时 客户端需要做的是 获取填充服务器信息, 并向服务器请求连接!

	// 填充服务器基本网络信息
	struct sockaddr_in server;
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(serverPort);
	inet_aton(serverIP.c_str(), &server.sin_addr);

	// 发送连接请求
	if (connect(sockFd, (const struct sockaddr*)&server, sizeof(server)) == -1) {
		// 连接失败
		logMessage(FATAL, "Client connect() faild: %d, %s", sockFd, strerror(errno));
		exit(CONNECT_ERR);
	}
	logMessage(DEBUG, "Client connect success.");

	// 连接成功之后, 就可以向服务器发送信息了
	std::string message;
	while (!quit) { // 根据退出状态 识别客户端是否退出
		message.clear();
		std::cout << "请输入表达式 >> ";
		std::getline(std::cin, message); // 从命令行获取消息 到 message中
		if (strcasecmp(message.c_str(), "quit") == 0) {
			// 我们实现了 输入 quit 这个单词就向服务器请求退出 的功能
			// 所以, 在输入 quit 这个单词时, 表示 需要退出
			// 就要将 客户端的退出状态设置为 true, 让客户端不进入下一次循环
			quit = true;
			continue;
		}

		request req;
		if (!makeRequest(message, &req)) {
			continue; // 初始化请求失败
		}

		// 请求创建并初始化成功之后, 就可以序列化 encode 然后发送了
		std::string package;
		req.serialize(&package);

		package = encode(package, package.size());

		ssize_t sW = write(sockFd, package.c_str(), package.size()); // 向客户端套接字文件描述符写入消息
		if (sW > 0) {
			// 写入成功, 就准备接收服务器的回复
			char buff[BUFFER_SIZE]; // 需要与服务器inbuffer大小一致
			ssize_t sR = read(sockFd, buff, sizeof(buff) - 1);
			if (sR > 0) {
				message[sR] = '\0';
			}
			std::string echoPackage = buff;

			// 接收成功服务器的回复, 就需要对接收到的数据 decode 和 反序列化
			response resp;
			uint32_t packageLen = 0;

			echoPackage = decode(echoPackage, &packageLen);

			if (packageLen) {
				// 解码成功, 并获取解码成功的字符串
				resp.deserialize(echoPackage);

				printf("[exitcode: %d] %d\n", resp.get_exitCode(), resp.get_result());
			}
		}
		else if (sW <= 0) {
			logMessage(FATAL, "Client write() faild: %d, %s", sockFd, strerror(errno));
			break;
		}
	}

	// 退出循环 客户端退出, 关闭文件描述符
	close(sockFd);

	return 0;
}
