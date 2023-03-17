#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using std::cout;
using std::endl;

int main() {
	pid_t id = fork();
	if(id == 0) {
		while(1) {
			cout << "我是子进程, 我不结束, 我的pid::" << getpid() << endl; 
			sleep(2);
		}
	}
	else {
		int cnt2 = 10;
		while(cnt2) {
			cout << "我是父进程, 我还剩 " << cnt2 << "s, 结束, 我的pid::" << getpid() << endl;
			sleep(1);
			cnt2--;
		}
	}

	return 0;
}
