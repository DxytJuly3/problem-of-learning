#include <stdio.h>
//有一个有序数字序列，从小到大排序，将一个新输入的数插入到序列中，保证插入新数后，序列仍然是升序。
int main()
{
    int n = 0;
    int arr[2000] = { 0 };
    int i = 0;
    int tmp = 0;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
    {
        scanf("%d", &tmp);
        arr[tmp] = tmp;
    }
    scanf("%d", &tmp);
    arr[tmp] = tmp;
    for(i = 0; i < 2000; i++)
    {
        if(arr[i] != 0)
            printf("%d ", arr[i]);
    }
    
    return 0;
}