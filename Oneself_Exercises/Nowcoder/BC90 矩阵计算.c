#include <stdio.h>
//输入NxM矩阵，矩阵元素均为整数，计算其中大于零的元素之和。
int main()
{
    int n = 0;
    int m = 0;
    int arr[100][100] = { 0 };
    int i = 0;
    int j = 0;
    scanf("%d %d", &n, &m);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    int sum = 0;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (arr[i][j] > 0)
                sum += arr[i][j];
        }
    }
    printf("%d", sum);

    return 0;
}