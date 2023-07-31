#include "tcpServer.hpp"

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
