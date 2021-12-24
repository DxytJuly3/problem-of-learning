#include <stdio.h>
//KiKi想知道一个n阶方矩是否为上三角矩阵，请帮他编程判定。上三角矩阵即主对角线以下的元素都为0的矩阵，主对角线为从矩阵的左上角至右下角的连线。
int main()
{
    int n = 0;
    scanf("%d", &n);
    int arr[10][10] = { 0 };
    int flag = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            scanf("%d", &arr[i][j]);
        }
    }
    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            if(arr[i][j] != 0)
            {
                flag = 1;
                break;
            }
        }
    }
    if(flag == 0)
        printf("YES\n");
    else
        printf("NO\n");
    
    return 0;
}