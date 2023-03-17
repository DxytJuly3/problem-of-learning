#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
	umask(0);
	
	int fd = open("new_log.txt", O_WRONLY | O_CREAT | O_APPEND);		// 以追加只写方式打开文件, 若文件不存在则创建文件    
	//int fd = open("new_log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);		//以清空只写方式打开文件, 若文件不存在则创建文件
	//int fd = open("new_log.txt", O_RDONLY);		//以只读方式打开文件, 只读打开一般都是已存在的文件
	if(fd < 0) {
		perror("open");
	}

	dup2(fd, 1);		// 将标准输出重定向到只写打开文件, 实现输出重定向
	const char *buffer = "Hello world, hello July\n";
	write(stdout->_fileno, buffer, strlen(buffer));

//	dup2(fd, 0);	// 将标准输入重定向到只读方式打开的文件, 实现输入重定向
//	char buffer[128];
//	// 从stdin中获取数据到buffer中
//	while(fgets(buffer, sizeof(buffer), stdin) != NULL) {
//		printf("%s", buffer);
//	}

	close(fd);

	return 0;
}
