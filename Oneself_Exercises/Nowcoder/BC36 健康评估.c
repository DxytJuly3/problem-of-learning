//当BMI指数为18.5～23.9时属正常，否则表示身体存在健康风险。编程判断人体健康情况。
#include <stdio.h>
 
int main()
{
    double weight = 0;
    double hight = 0;
    scanf("%lf%lf",&weight, &hight);
    if(weight / hight / hight >= 18.5 && weight / hight / hight <= 23.9)
        printf("Normal");
    else
        printf("Abnormal");
     
    return 0;
}