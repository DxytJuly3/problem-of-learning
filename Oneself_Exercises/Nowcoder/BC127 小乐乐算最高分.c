#include <stdio.h>
//小乐乐的老师BoBo想知道班级中谁的数学成绩最高，请编程帮他实现。
int main()
{
    int n = 0;
    scanf("%d", &n);
    int math = 0;
    scanf("%d", &math);
    int max = math;
    for(int i = 1; i < n; i++)
    {
        scanf("%d", &math);
        if(math > max)
            max = math;
    }
    printf("%d\n", max);
    
    return 0;
}