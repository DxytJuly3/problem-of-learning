.PHONY:all
all: initializer_list r_reference perfectForward

initializer_list: intializer_list_Test.cc 
	g++ -o $@ $^
r_reference: r_reference.cc
	g++ -o $@ $^
perfectForward: perfectForward.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -rf initializer_list r_reference perfectForward
