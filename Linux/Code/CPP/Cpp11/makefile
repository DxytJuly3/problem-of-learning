.PHONY:all
all: initializer_list r_reference perfectForward temp_var_para emplace_back lambda_test

initializer_list: intializer_list_Test.cc 
	g++ -o $@ $^
r_reference: r_reference.cc
	g++ -o $@ $^
perfectForward: perfectForward.cc
	g++ -o $@ $^
temp_var_para: temp_var_para.cc
	g++ -o $@ $^
emplace_back: emplace_back.cc
	g++ -o $@ $^
lambda_test: lambda_test.cc
	g++ -o $@ $^

.PHONY:clean
clean:
	rm -rf initializer_list r_reference perfectForward temp_var_para emplace_back lambda_test
