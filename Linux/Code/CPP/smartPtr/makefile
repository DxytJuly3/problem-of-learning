.PHONY:all
all: smartPtr smartPtrDebug

smartPtr: smartPtr.cc
	g++ -o $@ $^
smartPtrDebug: smartPtr.cc
	g++ -o $@ $^ -g

.PHONY:clean
clean:
	rm -rf smartPtr smartPtrDebug
