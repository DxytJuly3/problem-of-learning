#include <stdio.h>
//小乐乐输入百分制成绩，他想将成绩转换成等级制。转换规则为：
//90-100为’A’
//80-89为’B’
//70-79为’C’
//60-69为’D’
//59以下为’E’
//如果输入的成绩不在0-100之间，输出’F’。
int main()
{
    int score = 0;
    scanf("%d", &score);
    if(score >= 90 && score <= 100)
        printf("A\n");
    else if(score >= 80 && score <= 89)
        printf("B\n");
    else if(score >= 70 && score <= 79)
        printf("C\n");
    else if(score >= 60 && score <= 69)
        printf("D\n");
    else if(score >= 0 && score <= 59)
        printf("E\n");
    else
        printf("F\n");
    
    return 0;
}