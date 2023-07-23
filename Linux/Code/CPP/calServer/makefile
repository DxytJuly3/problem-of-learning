.PHONY:all
all:tcpServerd tcpClient

tcpServerd: tcpServer.cc
	g++ -o $@ $^ -L/lib64 -ljsoncpp  -lpthread
tcpClient: tcpClient.cc
	g++ -o $@ $^ -L/lib64 -ljsoncpp

.PHONY:clean
clean:
	rm -rf tcpServerd tcpClient
