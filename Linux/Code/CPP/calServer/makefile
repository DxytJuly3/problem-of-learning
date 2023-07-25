.PHONY:all
all:tcpServerd tcpClient

tcpServerd: tcpServer.cc
	g++ -o $@ $^ -ljsoncpp  -lpthread
tcpClient: tcpClient.cc
	g++ -o $@ $^ -ljsoncpp

.PHONY:clean
clean:
	rm -rf tcpServerd tcpClient
