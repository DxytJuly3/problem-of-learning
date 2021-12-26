#include <stdio.h>
//小乐乐的班级进行了一次期中考试，考试一共有3门科目：数学，语文，英语
//小乐乐的班主任决定给没有通过考核的同学家长开一次家长会，考核的标准是三科平均分不低于60分
//所以现在想请你帮忙算一算小乐乐会不会被叫家长。
int main()
{
    int Chinese = 0;
    int English = 0;
    int math = 0;
    scanf("%d%d%d", &Chinese, &English, &math);
    if(Chinese + English + math >= 180)
        printf("NO\n");
    else
        printf("YES\n");
    
    return 0;
}