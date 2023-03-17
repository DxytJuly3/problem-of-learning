#include <iostream>
#include <unistd.h>
using std::cout;
using std::endl;

int main() {
	pid_t id = fork();
	
	cout << "Hello, id = " << id << endl;

	return 0;
}
