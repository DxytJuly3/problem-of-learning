#include <stdio.h>
//KiKi这学期努力学习程序设计基础，要期末考试了，BoBo老师告诉他，总成绩包括四个部分，如下：
//总成绩 = 实验成绩 * 20% + 课堂表现成绩 * 10% + 过程考核成绩 * 20% + 期末上机考试成绩 * 50%
//现在输入KiKi的各项成绩，请计算KiKi的总成绩。
int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    double result=0.2 * a + 0.1 * b + 0.2 * c + 0.5 *d;
    printf("%.1lf",result);
    
    return 0;
}