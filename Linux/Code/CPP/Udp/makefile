.PHONY:all
all:udpServer udpClient

udpServer: udpServer.cc
	g++ -o $@ $^
udpClient: udpClient.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -rf udpServer udpClient
