#include <stdio.h>
//用户登录网站，通常需要注册，一般需要输入两遍密码。请编程判断输入的两次密码是否一致，一致输出“same”，不一致输出“different”
int main()
{
    char c1[100] = { 0 };
    char c2[100] = { 0 };
    scanf("%s", &c1);
    scanf("%s", &c2);
    if(strcmp(c1,c2) == 0)
        printf("same\n");
    else
        printf("different\n");
    
    return 0;
}