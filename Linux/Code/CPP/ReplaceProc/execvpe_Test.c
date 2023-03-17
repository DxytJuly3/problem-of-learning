#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define SIZE 128

int main() {
    extern char **environ;
    printf("\n为环境变量列表添加自定义环境变量：MYENV=DIY_ENVXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n");
    putenv((char*)"MYENV=DIY_ENVXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"); 

    pid_t id = fork();
    if(id == 0) {
        char *const execvpe_argv[SIZE] = { (char*)"./env_Test", NULL }; 

        printf("我是子进程, pid: %d, 即将调用execvpe()进程替换\n", getpid());
        execvpe("./env_Test", execvpe_argv, environ);
        printf("我是子进程, pid: %d, 进程替换失败\n", getpid());
    }
    else {
        pid_t ret = wait(NULL);
        if(ret > 0) {
            printf("我是父进程, 等待子进程成功\n\n");
        }
    }

    return 0;
}
