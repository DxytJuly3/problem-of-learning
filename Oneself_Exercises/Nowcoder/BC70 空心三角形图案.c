//KiKi学习了循环，BoBo老师给他出了一系列打印图案的练习，该任务是打印用“*”组成的“空心”三角形图案。
#include <stdio.h>

int main()
{
    int n = 0;
    int i = 0;
    int j = 0;
    while(scanf("%d", &n) != EOF)
    {
        for(i = 0; i < n; i++) //i表示第i行
        {
            for(j = 0; j < i + 1; j++)  //表示第j个
            {
                if((j == 0)|| (i == n - 1))    //j为0表示第一列，i为n-1表示最后一行
                    printf("* ");
                else if((j == i) && (i != n - 1))//j等于i并且i不等于n-1表示除了最后一行每一行的最后一个，即j==i
                    printf("* ");
                else
                    printf("  ");
            }
            printf("\n");
        }
    }
    
    return 0;
}