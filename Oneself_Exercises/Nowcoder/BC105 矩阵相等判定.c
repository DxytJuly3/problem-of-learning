#include <stdio.h>
//KiKi得到了两个n行m列的矩阵，他想知道两个矩阵是否相等，请你回答他。(当两个矩阵对应数组元素都相等时两个矩阵相等)。
int main()
{
    int n = 0;
    int m = 0;
    scanf("%d%d", &n, &m);
    int arr1[100] = { 0 };
    int arr2[100] = { 0 };
    int flag = 0;
    for(int i = 0; i < n * m; i++)
    {
        scanf("%d", &arr1[i]);
    }
    for(int i = 0; i < n * m; i++)
    {
        scanf("%d", &arr2[i]);
    }
    for(int i = 0; i < n * m; i++)
    {
        if(arr1[i] != arr2[i])
        {
            flag = 1;
            break;
        }
    }
    if(flag == 0)
        printf("Yes\n");
    else
        printf("No\n");
    
    return 0;
}