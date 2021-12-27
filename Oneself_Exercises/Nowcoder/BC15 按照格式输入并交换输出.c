#include <stdio.h>
//输入两个整数，范围-231~231-1，交换两个数并输出。
int main()
{
    int a = 0;
    int b = 0;
    int tmp = 0;
    scanf("a=%d,b=%d", &a, &b);
    //使用中间变量tmp来交换两个数字
    tmp = a;
    a = b;
    b = tmp;
    printf("a=%d,b=%d\n", a, b);
    
    return 0;
}