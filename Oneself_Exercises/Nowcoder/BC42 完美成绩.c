//从键盘输入一个整数表示的成绩，编程判断成绩是否在90~100之间，如果是则输出“Perfect”。
#include <stdio.h>
 
int main()
{
    int score = 0;
    scanf("%d", &score);
    if(score >= 90 && score <= 100)
        printf("Perfect");
     
    return 0;
}

