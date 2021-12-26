#include <stdio.h>
//小乐乐的班主任想统计一下班级里一共有多少人需要被请家长
//三个成绩（语文，数学，外语）平均分低于60的将被请家长
//小乐乐想编程帮助班主任算一下有多少同学被叫家长。
int main()
{
    int n = 0;
    int Chinese = 0;
    int English = 0;
    int math = 0;
    scanf("%d", &n);
    int count = 0;
    for(int i = 0; i < n; i++)
    {
        scanf("%d%d%d", &Chinese, &English, &math);
        if(Chinese + English + math < 180)
            count ++;
    }
    printf("%d\n", count);
    
    return 0;
}