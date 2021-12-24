#include <stdio.h>
//KiKi知道什么叫杨辉三角之后对杨辉三角产生了浓厚的兴趣，他想知道杨辉三角的前n行，请编程帮他解答。
//杨辉三角，本质上是二项式(a+b)的n次方展开后各项的系数排成的三角形。
//其性质包括：每行的端点数为1， 一个数也为1；每个数等于它左上方和上方的两数之和。
int main()
{
    int n = 0;
    scanf("%d", &n);
    int triangle[30][30] = { 0 };
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j || j == 0)
                triangle[i][j] = 1;
            else
            {
                triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(triangle[i][j] != 0)
                printf("%5d", triangle[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}