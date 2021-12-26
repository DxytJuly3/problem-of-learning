#include <stdio.h>
//KiKi知道了大一三科比较重要课程的分数
//包括：程序设计基础，高数，英语，请编程帮他找到三科中的最高分。
int main()
{
    int math = 0;
    scanf("%d", &math);
    int max = math;
    for(int i = 1; i < 3; i++)
    {
        scanf("%d", &math);
        if(math > max)
            max = math;
    }
    printf("%d\n", max);
    
    return 0;
}