# .PHONY:all
# all:myproc mykill

mykill:mykill.cc
	g++ $^ -o $@

myproc:myproc.cc
	g++ $^ -o $@

.PHONY:clean
clean:
	rm -f mykill myproc