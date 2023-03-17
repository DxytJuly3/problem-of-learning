#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using std::cout;
using std::endl;

int main() {
	cout << "I am a process, pid = " << getpid() << ", ppid = " << getppid() << endl;
	while(1) {}

	return 0;
}

