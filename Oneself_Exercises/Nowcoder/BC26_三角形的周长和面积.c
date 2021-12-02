//根据给出的三角形3条边a, b, c，计算三角形的周长和面积。

#include <stdio.h>
#include <math.h>
 
int main()
{
    double a = 0;
    double b = 0;
    double c = 0;
    scanf("%lf%lf%lf", &a, &b, &c);
    double circumference = a + b + c;
    double p = circumference / 2;
    printf("circumference=%.2lf area=%.2lf", circumference, sqrt(p*(p-a)*(p-b)*(p-c)));
     
    return 0;
}
