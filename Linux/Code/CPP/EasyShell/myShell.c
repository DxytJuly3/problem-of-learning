#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define SIZE 128

int putEnvInmyShell(char *put_Env) {
	putenv(put_Env);

	return 0;
}

int changeDir(const char* new_path) {
	chdir(new_path);					// 系统调用
	
	return 0;
}
char *command_argV[SIZE];

char copy_env[SIZE];

int main() {
    while(1) {
        char command_S[SIZE];
        memset(command_S, '\0', SIZE);

        // 首先是用户提示符: 
        printf("[七月July@MyBlog 当前目录]# ");
        fgets(command_S, SIZE, stdin);
        command_S[strlen(command_S) - 1] = '\0';        // 修改'\n' 为 '\0'
        
        // 分割命令行
        command_argV[0] = strtok(command_S, " ");
        int index = 1;
        if(strcmp(command_argV[0], "ls") == 0) {
            command_argV[index++] = "--color=auto";         // 若执行ls命令, 则在ls命令后携带一个--color=auto选项
        } 
        if(strcmp(command_argV[0], "ll") == 0) {
            command_argV[0] = "ls";
            command_argV[index++] = "-l";
            command_argV[index++] = "--color=auto";
        }
        while(command_argV[index++] = strtok(NULL, " "));
        // strtok分割不到字符串时, 会返回空指针, 刚好可以作为循环结束的条件
        

		// 内建命令
		if(strcmp(command_argV[0], "cd") == 0 && command_argV[1] != NULL) {
			// 使用cd命令时, command_argV[1]位置应该是需要进入的路径
			changeDir(command_argV[1]);
			continue;								// 非子进程命令, 不用执行下面的代码, 所以直接进入下个循环
		}
		if(strcmp(command_argV[0], "export") == 0 && command_argV[1] != NULL) {
			// 我们接收的命令, 都在command_S 字符串中, 此字符串每次循环都会被清除
			// 所以不能直接将 command_argV[1] putenv到环境变量中, 因为指向的同一块地址
			// 所以 需要先拷贝一份
			strcpy(copy_env, command_argV[1]);
			putEnvInmyShell(copy_env);
			continue;
		}


        // 创建子进程, 并进程替换
        pid_t id = fork();
        if(id == 0) {
            //进程替换
            execvp(command_argV[0], command_argV);
            exit(-1);       // 替换失败则 退出码-1
        }
        // 父进程回收子进程
        int status = 0;
        pid_t ret = waitpid(id, &status, 0);
		if(ret < 0) {
			exit(-1);
		}
    }

    return 0;
}
