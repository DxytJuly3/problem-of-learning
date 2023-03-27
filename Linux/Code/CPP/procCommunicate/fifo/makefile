.PHONY:all
all:clientFifo serverFifo

clientFifo:clientFifo.cpp
	g++ $^ -o $@
serverFifo:serverFifo.cpp
	g++ $^ -o $@

.PHONY:clean
clean:
	rm -f clientFifo serverFifo .fifo