#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using std::cout;
using std::endl;

int main() {
	pid_t id = fork();
	
	if(id == 0) {
		cout << "我是子进程, 我的pid是" << getpid() << ", 我运行结束了" << endl;
	}
	else {
		cout << "我是父进程, 我的pid是" << getpid() << ", 我运行没有结束" << endl;
		while(1) {}
	}
	
	return 0;
}
