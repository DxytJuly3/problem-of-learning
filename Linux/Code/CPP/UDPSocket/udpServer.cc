#include <iostream>
#include <string>
#include <unordered_map>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "logMessage.hpp"

using std::cout;
using std::endl;
using std::string;
using std::unordered_map;

// 封装UDP服务
class udpServer {
public:
	// 构造函数, 需要传入 port 和 ip
	// ip 可以缺省, 因为 ip可以默认为空, 后面解释理由
	udpServer(uint16_t port, string ip = "")
		: _port(port)
		, _ip(ip)
		, _sockFd(-1) {}
	// 析构函数
	~udpServer() {}

	// 服务器初始化函数
	// 具体功能就是 创建套接字 绑定主机网络信息
	void init() {
		// 1. 首先就是创建套接字, 并获取套接字文件描述符
		_sockFd = socket(AF_INET, SOCK_DGRAM, 0);

		if (_sockFd < 0) {
			// 套接字文件描述符创建失败
			logMessage(FATAL, "socket() faild:: %s : %d", strerror(errno),
					   _sockFd);
			exit(1);
		}

		logMessage(DEBUG, "socket create success: %d", _sockFd);

		// 套接字创建成功之后, 就是将网络信息绑定到 主机上了
		// 2. 绑定网络信息
		//		bind(int __fd, const struct sockaddr *__addr, socklen_t __len);
		//
		// 2.1 将网络信息 填充到 struct sockaddr_in 结构体中
		//		此结构体中 填充的内容是 需要在网络中存在的内容
		//		比如, 协议 IP 端口号等, 只有这些东西 在网络上存在, 其他主机才能与服务器通信
		struct sockaddr_in local;
		std::memset(&local, 0, sizeof(local));

		// 填充网络信息
		// 1. 地址类型, 选择协议 通信方式
		local.sin_family = AF_INET;
		// 2. 端口号
		//	  端口号是需要向网络中发送的, 所以 需要从本地字节序 转换成网络字节序
		local.sin_port = htons(_port);
		// 3. IP
		//    IP 不能直接填充到结构体中, 因为类中的 _ip 是字符串,  而网络中的IP 通常用4字节的二进制表示, 结构体中同样是此类型 in_addr_t = uint32_t
		//    所以 还需要将 点分十进制字符串型的_ip 转换为 uint32_t 才能填充到 结构体中
		local.sin_addr.s_addr =
			_ip.empty() ? htonl(INADDR_ANY) : inet_addr(_ip.c_str());
		// 这里使用了三目运算符 ? : 用来判断 传入的 ip 是否为空
		//	如果传入的IP为空, 则将 INADDR_ANY 这个 IP 填充到结构体中, 否则就将 _ip字符串 转换为 in_addr_t 类型, 然后填充到结构体中
		//	INADDR_ANY 其实是 强转为 in_addr_t 类型的 0.
		//	1. 网络服务器 使用 INADDR_ANY 作为IP, 绑定到主机中. 表示监听本机上所有的IP 网络接口.
		//	   一台服务器主机可能有许多的IP, 使用 INADDR_ANY 意思就是说, 其他主机可以通过服务器主机上的 任意IP:指定port 找到服务器进程实现通信
		//	2. 当绑定指定的IP时, 就表示 其他主机只能通过服务器主机上的 指定IP:指定port 找到服务器进程实现通信.
		//	   如果使用其他本机上的IP:指定port, 服务器是不会响应的. 因为服务器进程 只接收通过指定 IP 发送给服务器进程的信息
		// IP也是要向网络中发送的, 所以要将 IP转换成网络字节序. inet_addr() 则会自动将ip转换为网络字节序

		// 填充完网络信息, 就要将网络信息 绑定到操作系统内核中, 进而将网络信息 发送到网络上
		if (bind(_sockFd, (const struct sockaddr*)&local, sizeof(local)) ==	-1) {
			// 绑定失败
			logMessage(FATAL, "bind() faild:: %s : %d", strerror(errno), _sockFd);
			exit(2);
		}
		// 绑定成功
		logMessage(DEBUG, "socket bind success : %d", _sockFd);
	}

	// 服务器运行函数
	// 具体功能 实际上是 循环地监听、接收发送到服务器上的信息
	void start() {
		// 很多服务器本质上是一个死循环
		char inBuffer[1024]; // 用来存储发送过来的信息
		while (1) {
			struct sockaddr_in peer; // 输出型参数, 用来接收对方主机网络信息
			socklen_t peerLen = sizeof(peer); // 输入输出型参数

			// 接收发送到服务器上的信息, 以及发送端的网络信息
			// recvfrom(int __fd, void *__restrict __buf, size_t __n, int __flags, struct sockaddr *__restrict __addr, socklen_t *__restrict __addr_len);
			// 后两个参数 即为接收发送端网络信息的输出型参数
			// 返回值 是 接收到发送过来的信息的字节数, 即放在 inBuffer里的字节数
			// 接收失败则返回 -1
			ssize_t s = recvfrom(_sockFd, inBuffer, sizeof(inBuffer) - 1, 0,
								 (struct sockaddr*)&peer, &peerLen);

			if (s > 0) {
				// 当字符串结尾
				inBuffer[s] = 0;
			}
			else if (s == -1) {
				logMessage(WARINING, "recvfrom() error:: %s : %d",
						   strerror(errno), _sockFd);
				continue;
			}

			// 读取成功, 除了读取到对方的数据，你还要读取到对方的网络地址[ip:port]
			string peerIp = inet_ntoa(peer.sin_addr); //拿到了对方的IP
			uint32_t peerPort = ntohs(peer.sin_port); // 拿到了对方的port

			// 检查用户是否在服务器中, 不在则添加用户
			checkOnlineUser(peerIp, peerPort, peer);

			// 打印出来对方给服务器发送过来的消息
			logMessage(NOTICE, "[%s:%d]%s", peerIp.c_str(), peerPort, inBuffer);

			// 然后将消息转发到所有用户的客户端上, 实现多人聊天
			string infoUser(inBuffer);
			messageRoute(peerIp, peerPort, infoUser);
		}
	}

	void checkOnlineUser(string& ip, uint32_t port, struct sockaddr_in& peer) {
		string key = ip;
		key += ":";
		key += std::to_string(port);
		auto itUser = _users.find(key);

		// 判断用户是否已经存在, 不存在则添加
		if (itUser == _users.end()) {
			_users.insert({key, peer});
		}
	}

	void messageRoute(string& ip, uint32_t port, string info) {
		string message = "[";
		message += ip;
		message += ":";
		message += std::to_string(port);
		message += "]";
		message += info;

		// 遍历 服务器用户列表, 将message 发送给每一个在服务器内的用户网络进程
		for (auto& user : _users) {
			sendto(_sockFd, message.c_str(), message.size(), 0,
				   (struct sockaddr*)&(user.second), sizeof(user.second));
		}
	}

private:
	// 服务器 端口号
	uint16_t _port;
	// 服务器 IP, 程序运行时, 一般传入的是 点分十进制表示的ip的字符串
	string _ip;
	// 服务器 套接字文件描述符
	int _sockFd;
	// 服务器用户   key: ip:port, T:主机网络进程信息
	unordered_map<string, struct sockaddr_in> _users;
};

static void Usage(const string porc) {
	cout << "Usage:\n\t" << porc << " port [ip]" << endl;
}

// main 函数需要获取命令函参数, 以实现获取端口号和ip
int main(int argc, char* argv[]) {
	// 如果 使用方法错误
	if (argc != 2 && argc != 3) {
		Usage(argv[0]);
		exit(3);
	}

	// 获取 端口号 和 IP
	uint16_t port = atoi(argv[1]);
	string ip;
	if (argc == 3) {
		ip = argv[2];
	}

	// 使用端口号和IP 实例化udpServer对象
	udpServer uSvr(port, ip);

	// 初始化, 并启动服务器
	uSvr.init();
	uSvr.start();

	return 0;
}
