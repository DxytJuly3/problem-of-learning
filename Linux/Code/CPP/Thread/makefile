.PHONY:all
all:myThread threadTest myThreadID

myThreadID:myThreadID.cc 
	g++ -o $@ $^ -lpthread
myThread:myThread.cc
	g++ -o $@ $^ -lpthread
threadTest:threadTest.cc
	g++ -o $@ $^ -lpthread

.PHONY:clean
clean:
	rm -f myThread threadTest myThreadID