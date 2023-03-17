#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    extern char **environ;
    
//    char *const envp[] = { 
//        (char*)"MYENV1=DIY_ENV1",
//        (char*)"MYENV2=DIY_ENV2",
//        NULL 
//    };

    putenv((char*)"MYENV=DIY_ENV111111111111111111111111111111111111111111111");
    pid_t id = fork();
    if(id == 0) {
        printf("我是子进程, pid: %d\n", getpid());
        execle("./env_Test", "./env_Test", NULL, environ);
        //execle("./env_Test", "./env_Test", NULL, envp);
        printf("我自己进程, pid: %d\n", getpid());
    }
    else {
        pid_t ret = wait(NULL);
        if(ret > 0) {
            printf("我是父进程, 等待子进程成功\n");
        }
    }

    return 0;
}
