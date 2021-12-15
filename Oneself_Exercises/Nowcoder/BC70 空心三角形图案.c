#include <stdio.h>
//BoBo老师给他出了一系列打印图案的练习，该任务是打印用“*”组成的“空心”三角形图案
int main()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        int i = 0;
        int j = 0;
        for (i = 1; i <= n; i++)
        {
            for (j = 1; j <= n; j++)
            {
                if (j == i || j == 1 || i == n)
                    printf("* ");
                else
                    printf("  ");
            }
            printf("\n");
        }
    }

    return 0;
}