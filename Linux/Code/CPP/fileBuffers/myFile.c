#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h> 

int main() {
	printf("Hello world");
	write(stdout->_fileno, "I am a process", strlen("I am a process"));

	sleep(3);

	return 0;
}
