#include <stdio.h>
#include <unistd.h>
int global_Var = 100;

int main() {
	pid_t id = fork();
	if(id == 0) {
		int cnt = 5;
		while(1) {
			if(cnt > 0) {
				printf("我是子进程, global_Var= %d, addr=%p, 还有 %ds 修改global_Var\n", global_Var, &global_Var, cnt);
				cnt--;
				if(cnt == 0) {
					global_Var = 200;
					printf("我是子进程, 我已修改global_Var\n");
				}
			}
			else
				printf("我是子进程, global_Var= %d, addr=%p\n", global_Var, &global_Var);
			sleep(1);
		}
	}
	else {
		while(1) {
			printf("我是父进程, global_Var= %d, addr=%p\n\n", global_Var, &global_Var);
			sleep(2);	
		}
     }

	return 0;
}
