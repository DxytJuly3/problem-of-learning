.PHONY:all
all:ipcShmClient ipcShmServer

ipcShmClient:ipcShmClient.cpp
	g++ $^ -o $@
ipcShmServer:ipcShmServer.cpp
	g++ $^ -o $@

.PHONY:clean
clean:
	rm -f ipcShmClient ipcShmServer .fifo