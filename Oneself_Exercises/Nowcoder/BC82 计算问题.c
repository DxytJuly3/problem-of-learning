#include <stdio.h>
//这是一个非常简单的题目，意在考察你编程的基础能力。千万别想难了哦。输入为一行，包括了用空格分隔的四个整数a、b、c、d（0 < a, b, c, d < 100,000）。输出为一行，为“(a+b-c)*d”的计算结果。
int main()
{
    int a = 0, b = 0, c = 0, d = 0;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    printf("%d", (a + b - c) * d);
    
    return 0;
}