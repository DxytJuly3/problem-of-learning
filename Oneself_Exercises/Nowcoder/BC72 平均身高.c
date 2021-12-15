#include <stdio.h>
//从键盘输入5个人的身高（米），求他们的平均身高（米）
int main()
{
    double hight1 = 0,hight2 = 0,hight3 = 0,hight4 = 0,hight5 = 0;
    scanf("%lf%lf%lf%lf%lf", &hight1, &hight2, &hight3, &hight4, &hight5);
    printf("%.2lf",( hight1 + hight2 + hight3 + hight4 + hight5 ) / 5);
    
    return 0;
}