#include <iostream>
#include <unistd.h>
using std::cout;
using std::endl;

int main() {
	cout << "I am a Process, PID = " << getpid() << endl;

	return 0;
}
