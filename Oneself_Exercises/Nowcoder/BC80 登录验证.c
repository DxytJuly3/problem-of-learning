#include <stdio.h>
#include <string.h>
//有个软件系统登录的用户名和密码为（用户名：admin，密码：admin），用户输入用户名和密码，判断是否登录成功。
int main()
{
    char s2[5] = { 0 };
    char s3[5] = { 0 };
    while (scanf("%s%s", &s2, &s3) != EOF)
    {
        if (strcmp(s2, "admin") == 0 && strcmp(s3, "admin") == 0)
            printf("Login Success!\n");
        else
            printf("Login Fail!\n");
    }

    return 0;
}