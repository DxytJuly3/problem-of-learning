.PHONY:all
all:myThread threadTest

myThread:myThread.cc
	g++ -o $@ $^ -lpthread
threadTest:threadTest.cc
	g++ -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -f myThread threadTest