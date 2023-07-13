.PHONY:all
all: threadPool

threadPool: threadPool.cc
	g++ -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -rf threadPool
