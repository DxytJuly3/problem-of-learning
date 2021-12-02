//给定一个球体的半径，计算其体积。其中球体体积公式为 V = 4/3*πr3，其中 π = 3.1415926。
#include <stdio.h>
#define pi 3.1415926
 
int main()
{
    double r = 0;
    scanf("%lf", &r);
    printf("%.3lf", 4*pi*r*r*r/3);
     
    return 0;
}