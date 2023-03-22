.PHONY:all
all:myMath.o myPrint.o

myPrint.o:myPrint.c
	gcc -fPIC -c $^ -o $@
myMath.o:myMath.c
	gcc -fPIC -c $^ -o $@

.PHONY:clean
clean:
	rm -f myPrint.o myMath.o
