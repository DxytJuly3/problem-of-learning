#include <stdio.h>
//输入一个整数序列，判断是否是有序序列，有序，指序列中的整数从小到大排序或者从大到小排序(相同元素也视为有序)。
int main()
{
    int n = 0;
    scanf("%d", &n);
    int i = 0;
    int arr[50] = { 0 };
    int flag1 = 0;
    int flag2 = 0;
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    for(i = 0; i < n; i++)
    {
        if(arr[i] <= arr[i+1])
            flag1++;
        else
            break;
    }
    for(i = 0; i < n; i++)
    {
        if(arr[i] >= arr[i+1])
            flag2++;
        else
            break;
    }
    if(flag1 == n-1 || flag2 == n)
        printf("sorted\n");
    else
        printf("unsorted\n");
    
    return 0;
}