#include <stdio.h>
//KiKi有一个矩阵，他想知道转置后的矩阵（将矩阵的行列互换得到的新矩阵称为转置矩阵），请编程帮他解答。
int main()
{
    int n = 0;
    int m = 0;
    int arr[10][10] = { 0 };
    int i = 0;
    int j = 0;
    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    for (j = 0; j < m; j++)
    {
        for (i = 0; i < n; i++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }

    return 0;
}