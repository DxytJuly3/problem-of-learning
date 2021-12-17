#include <stdio.h>
//输入n科成绩（浮点数表示），统计其中的最高分，最低分以及平均分。
int main()
{
    int n = 0;
    double score = 0;
    double max = 0;
    double min = 100;
    int i = 0;
    double sum = 0;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        scanf("%lf", &score);
        if(score > max)
            max = score;
        if(score < min)
            min = score;
        sum += score;
    }
    printf("%.2lf %.2lf %.2lf", max, min, sum / n);
    
    return 0;
}