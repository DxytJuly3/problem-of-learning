.PHONY:all
all:myproc mykill blockshow

blockshow:blockshow.cc
	g++ $^ -o $@
mykill:mykill.cc
	g++ $^ -o $@
myproc:myproc.cc
	g++ $^ -o $@

.PHONY:clean
clean:
	rm -f mykill myproc blockshow