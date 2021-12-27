#include <stdio.h>
//依次输入一个学生的学号，以及3科（C语言，数学，英语）成绩，在屏幕上输出该学生的学号，3科成绩（注：输出成绩时需进行四舍五入且保留2位小数）。
int main()
{
    int num = 0;
    float scoreC = 0,scoreM = 0,scoreE = 0;
    scanf("%d;%f,%f,%f",&num,&scoreC,&scoreM,&scoreE);
    printf("The each subject score of  No. %d is %.2f, %.2f, %.2f.\n",num,scoreC,scoreM,scoreE);
    
    return 0;
}