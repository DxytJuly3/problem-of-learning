#include <stdio.h>
//小乐乐学会了自定义函数，BoBo老师给他出了个问题，根据以下公式计算m的值。
//其中 max3函数为计算三个数的最大值，如： max3(1, 2, 3) 返回结果为3。
double max3(int a, int b, int c)
{
    if(b > a)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }
    if(c > a)
    {
        int tmp = a;
        a = c;
        c = tmp;
    }
    return a;
}

int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    scanf("%d%d%d", &a, &b, &c);
    printf("%.2lf",max3(a+b, b, c) / (max3(a, b+c, c) + max3(a, b, b+c)));
    
    return 0;
}