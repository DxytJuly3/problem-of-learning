.PHONY:all
all:libMyfun.a libMyfun.so

libMyfun.so:myPrint.o myMath.o
	gcc -shared $^ -o $@
myPrint.o:myPrint.c
	gcc -fPIC -c $^ -o $@
myMath.o:myMath.c
	gcc -fPIC -c $^ -o $@

libMyfun.a:myPrint_s.o myMath_s.o
	ar -rc $@ $^
myMath_s.o:myMath.c
	gcc -c $^ -o $@
myPrint_s.o:myPrint.c
	gcc -c $^ -o $@

.PHONY:lib
lib:
	mkdir -p lib-static/lib
	mkdir -p lib-static/include
	mkdir -p lib-dynamic/lib
	mkdir -p lib-dynamic/include
	cp *.a lib-static/lib
	cp *.h lib-static/include
	cp *.so lib-dynamic/lib
	cp *.h lib-dynamic/include

.PHONY:clean
clean:
	rm -rf *.a *.o *.so lib-static lib-dynamic 
