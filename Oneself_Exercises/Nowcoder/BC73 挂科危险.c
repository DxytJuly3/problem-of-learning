#include <stdio.h>
//KiKi想知道这学期他的学习情况，BoBo老师告诉他这学期挂的科目累计的学分
//根据所挂学分，判断KiKi学习情况，10分以上：很危险(Danger++)，4~9分：危险(Danger)，0~3:Good
int main()
{
    int score = 0;
    while(scanf("%d", &score) != EOF)
    {
        if(score >= 10)
            printf("Danger++\n");
        else if(score >= 4 && score <= 9)
            printf("Danger\n");
        else
            printf("Good\n");
    }
    
    return 0;
}