#include <stdio.h>
//给定n个整数和一个整数x，小乐乐想从n个整数中判断x出现几次，请编程帮他实现。
int main()
{
    int n = 0;
    int arr[100] = { 0 };
    int count = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int search = 0;
    scanf("%d", &search);
    for(int i = 0; i < n; i++)
    {
        if(arr[i] == search)
            count++;
    }
    printf("%d", count);
    
    return 0;
}