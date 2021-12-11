#include <stdio.h>
//KiKi学习了循环，BoBo老师给他出了一系列打印图案的练习，该任务是打印用“*”组成的菱形图案。
int main()
{
    int n = 0;
    while(scanf("%d", &n) != EOF)
    {
        int i = 0;
        int j = 0;
        for(i = 0; i < n; i++)
        {
            for(j = n; j > i; j--)
            {
                printf(" ");
            }
            for(j = 0; j <= i; j++)
            {
                printf("* ");
            }
            printf("\n");
        }
        for(i = n + 1; i > 0; i--)
        {
            for(j = 0; j < n - i + 1; j++)
                printf(" ");
            for(j = i; j > 0; j--)
                printf("* ");
            printf("\n");
        }
    }
    
    return 0;
}