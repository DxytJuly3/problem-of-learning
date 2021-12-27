#include <stdio.h>
//给定两个整数a和b (0 < a,b < 10,000)，计算a除以b的整数商和余数。
int main()
{
    int a = 0;
    int b = 0;
    scanf("%d %d", &a, &b);
    printf("%d %d", a / b, a % b);
    
    return 0;
}