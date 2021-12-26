#include <stdio.h>
//小乐乐输入三科成绩，请编程帮他输出三科成绩总分及平均分。
int main()
{
    double sum = 0;
    double score = 0;
    for(int i = 0; i < 3; i++)
    {
        scanf("%lf", &score);
        sum += score;
    }
    printf("%.2lf %.2lf", sum, sum / 3);
    
    return 0;
}