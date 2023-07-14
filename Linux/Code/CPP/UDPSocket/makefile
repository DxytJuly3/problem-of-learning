.PHONY:all
all:udpServer udpClient

udpServer: udpServer.cc
	g++ -o $@ $^
udpClient: udpClient.cc
	g++ -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -rf udpServer udpClient
