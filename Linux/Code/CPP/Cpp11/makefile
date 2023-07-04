.PHONY:all
all: initializer_list r_reference

initializer_list: intializer_list_Test.cc 
	g++ -o $@ $^
r_reference: r_reference.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -rf initializer_list r_reference
