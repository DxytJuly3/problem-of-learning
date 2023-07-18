.PHONY:all
all:tcpServerd tcpClient

tcpServerd: tcpServer.cc
	g++ -o $@ $^ -lpthread
tcpClient: tcpClient.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -rf tcpServerd tcpClient
