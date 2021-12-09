#include <stdio.h>
//计算单位阶跃函数
int main()
{
    double t = 0;
    while(scanf("%lf", &t) != EOF)
    {
        if(t > 0)
            printf("1\n");
        else if(t == 0)
            printf("0.5\n");
        else
            printf("0\n");
    }
    
    return 0;
}