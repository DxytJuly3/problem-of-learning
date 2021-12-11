#include <stdio.h>
//KiKi学习了循环，BoBo老师给他出了一系列打印图案的练习，该任务是打印用“*”组成的翻转直角三角形图案。
int main()
{
    int n = 0;
    while(scanf("%d", &n) != EOF)
    {
        int i = 0;
        int j = 0;
        for(i = n; i > 0; i--)
        {
            for(j = 0; j < i; j++)
                printf("* ");
            printf("\n");
        }
        
    }
    
    return 0;
}