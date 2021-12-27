#include <stdio.h>
// 从键盘输入5个学生的成绩（整数），求他们的平均成绩（浮点数，保留一位小数）。
int main()
{
    int n = 0;
    int sum = 0;
    double avg = 0;
    for(int i = 0; i < 5; i++)
    {
        scanf("%d", &n);
        sum += n;
    }
    avg = sum / 5.0;
    printf("%.1lf", avg);
    
    return 0;
}