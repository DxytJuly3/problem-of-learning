#include <stdio.h>
//衡量人体胖瘦程度
int main()
{
    int weight = 0;
    int hight = 0;
    while(scanf("%d%d", &weight, &hight) != EOF)
    {
        double high = hight / 100.0;
        if(weight / (high * high) < 18.5)
            printf("Underweight\n");
        else if((weight / (high * high) >= 18.5) && (weight / (high * high) <= 23.9))
            printf("Normal\n");
        else if((weight / (high * high) > 23.9) && (weight / (high * high) <= 27.9))
            printf("Overweight\n");
        else
            printf("Obese\n");
    }
    
    return 0;
}