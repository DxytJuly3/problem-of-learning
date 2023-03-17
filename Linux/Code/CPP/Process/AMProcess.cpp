#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using std::cout;
using std::endl;

int main() {
	while(1) {
		cout << "I am a Process, myPID::" << getpid() << ", myPPID::" << getppid() << endl;
		sleep(1);
	}

	return 0;
}
