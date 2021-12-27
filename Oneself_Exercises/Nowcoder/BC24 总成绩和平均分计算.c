#include<stdio.h>
//依次输入一个学生的3科成绩，在屏幕上输出该学生的总成绩以及平均成绩。
int main()
{
    double a = 0;
    double b = 0;
    double c = 0;
    double sum = 0;
    double avg = 0;
    scanf("%lf%lf%lf", &a, &b, &c);
    sum = a + b + c;
    avg = sum / 3.0;
    printf("%.2lf %.2lf",sum,avg);
    
    return 0;
}