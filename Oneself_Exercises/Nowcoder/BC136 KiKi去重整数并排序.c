#include <stdio.h>
//给定一个整数序列，KiKi想把其中的重复的整数去掉，并将去重后的序列从小到大排序输出。
int main()
{
    int n = 0;
    scanf("%d", &n);
    int arr[1001] = { 0 };
    for(int i = 0; i < n; i++)
    {
        int tmp = 0 ;
        scanf("%d", &tmp);
        arr[tmp] = tmp;
    }
    for(int i = 0; i < 1001; i++)
    {
        if(arr[i] != 0)
            printf("%d ", arr[i]);
    }
    
    return 0;
}