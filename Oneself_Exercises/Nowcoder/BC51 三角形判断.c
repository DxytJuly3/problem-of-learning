#include <stdio.h>
//三角形判断
int main()
{
    int a = 0;
    int b = 0;
    int c = 0;
    while(scanf("%d%d%d", &a, &b, &c) != EOF)
    {
        if((a + b > c) && (a + c > b) && (c + b > a))
        {
            if(a == b && b == c)//只能先判断全等三角形
                printf("Equilateral triangle!\n");
            else if(a == b || b == c || c == a)
                printf("Isosceles triangle!\n");
            else
                printf("Ordinary triangle!\n");
        }
        else
            printf("Not a triangle!\n");
    }
    
    return 0;
}