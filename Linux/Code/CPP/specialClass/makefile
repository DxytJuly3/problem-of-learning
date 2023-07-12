.PHONY:all
all: specialClass singlePat

specialClass: specialClass.cc
	g++ -o $@ $^
singlePat: singlePat.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -rf specialClass singlePat
