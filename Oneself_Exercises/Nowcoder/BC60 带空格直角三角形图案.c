#include <stdio.h>

int main()
{//KiKi学习了循环，BoBo老师给他出了一系列打印图案的练习，该任务是打印用“*”组成的带空格直角三角形图案。
    int n = 0;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0; i < n; i++)
        {
            for(int k = n - i -1 ; k > 0; k--)
            {
                printf("  ");
            }
            for(int j = 0; j <= i; j++)
            {
                printf("* ");
            }
            printf("\n");
        }
    }
    
    return 0;
}