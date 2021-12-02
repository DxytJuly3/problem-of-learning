//从键盘任意输入一个整数表示的分数，如果及格，即：分数大于等于60分，是输出“Pass”，否则，输出“Fail”。
#include <stdio.h>
 
int main()
{
    int score = 0;
    while(~scanf("%d", &score))
    {
        if(score >= 60)
            printf("Pass\n");
        else
            printf("Fail\n");
    }
     
    return 0;
}