#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h> 

int main() {
	const char* str1 = "Hello printf\n";
	const char* str2 = "Hello fprintf\n";
	const char* str3 = "Hello fputs\n";
	const char* str4 = "Hello write\n";

	// C库函数
	printf("%s", str1);
	fprintf(stdout, str2);
	fputs(str3, stdout);

	// 系统接口
	write(stdout->_fileno, str4, strlen(str4));

	fork();
//	printf("Hello July");
//	fprintf(stdout, "Hello July");
//	fputs("Hello July", stdout);
	// 如果没有关闭stdout, 这三个语句会在进程结束时正常输出

	// 进程退出会自动刷新缓冲区
	// 我们在这里将 stdout 关闭
	// close(stdout->_fileno);

//	printf("Hello world");
//	write(stdout->_fileno, "I am a process", strlen("I am a process"));
//
//	sleep(3);

	return 0;
}
