.PHONY:all
all:tcpServerd tcpClient

tcpServerd: tcpServer.cc
	g++ -o $@ $^ -std=c++11 -ljsoncpp  -lpthread
tcpClient: tcpClient.cc
	g++ -o $@ $^ -std=c++11 -ljsoncpp

.PHONY:clean
clean:
	rm -rf tcpServerd tcpClient
