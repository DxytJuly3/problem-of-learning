#include <stdio.h>
//问题：一年约有 3.156×107 s，要求输入您的年龄，显示该年龄合多少秒。
int main()
{
    int year = 0;
    scanf("%d", &year);
    long long second = year * 31560000;
    printf("%lld", second);
    
    return 0;
}