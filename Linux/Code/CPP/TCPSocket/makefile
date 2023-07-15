.PHONY:all
all:tcpServer tcpClient

tcpServer: tcpServer.cc
	g++ -o $@ $^ -lpthread
tcpClient: tcpClient.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -rf serverTCP clientTCP
