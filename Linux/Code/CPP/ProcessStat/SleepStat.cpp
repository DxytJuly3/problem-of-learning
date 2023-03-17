#include <iostream>
#include <unistd.h>

int main() {
	while(1) {
		std::printf("I am a process, pid = %d\n", getpid());
	} 

	return 0;
}
