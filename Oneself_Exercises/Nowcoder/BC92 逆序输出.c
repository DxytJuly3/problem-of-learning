#include <stdio.h>
//输入10个整数，要求按输入时的逆序把这10个数打印出来。逆序输出，就是按照输入相反的顺序打印这10个数。
int main()
{
    int arr[10] = { 0 };
    int i = 0;
    for(i = 0; i < 10; i++)
    {
        scanf("%d", &arr[i]);
    }
    for(i = 9; i >= 0; i--)
    {
        printf("%d ", arr[i]);
    }
    
    return 0;
}