#include <iostream>
#include <unistd.h>
using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
	for(int i = 0; i < argc; i++) {
		cout << "argv[" << i << "] : " << argv[i] << endl;
	}
	
	return 0;
}
