//输入一个十六进制数a，和一个八进制数b，输出a+b的十进制结果（范围-231~231-1）。
#include <stdio.h>
 
int main()
{
    int a = 0;
    int b = 0;
    scanf("%x%o", &a, &b);
    printf("%d",a + b);
     
    return 0;
}