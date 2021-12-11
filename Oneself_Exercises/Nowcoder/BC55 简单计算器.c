#include <stdio.h>
//KiKi实现一个简单计算器，实现两个数的“加减乘除”运算
//用户从键盘输入算式“操作数1运算符操作数2”，计算并输出表达式的值
//如果输入的运算符号不包括在（+、-、*、/）范围内，输出“Invalid operation!”
//当运算符为除法运算，即“/”时。
//如果操作数2等于0.0，则输出“Wrong!Division by zero!”
int main()
{
    double x1 = 0;
    double x2 = 0;
    char n = 0;
    scanf("%lf%c%lf", &x1, &n, &x2);
    if(n == '+' || n == '-' || n == '*' || n == '/')
    {
        if(n == '+')
            printf("%.4lf+%.4lf=%.4lf\n", x1, x2, x1 + x2);
        if(n == '-')
            printf("%.4lf-%.4lf=%.4lf\n", x1, x2, x1 - x2);
        if(n == '*')
            printf("%.4lf*%.4lf=%.4lf\n", x1, x2, x1 * x2);
        if(n == '/')
        {
            if( x2 == 0)
                printf("Wrong!Division by zero!\n");
            else
                printf("%.4lf/%.4lf=%.4lf\n", x1, x2, x1 / x2);
        }
    }
    else
        printf("Invalid operation!\n");
    
    return 0;
}