#include <stdio.h>
//有一个整数序列（可能有重复的整数），现删除指定的某一个整数
//输出删除指定数字之后的序列，序列中未被删除数字的前后位置没有发生改变。
int main()
{
    int n = 0;
    scanf("%d", &n);
    int arr[50] = { 0 };
    int tmp = 0;
    int i = 0;
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &tmp);
    for(i = 0; i < n; i++)
    {
        if(arr[i] == tmp)
        {
            arr[i] = 0;
        }
    }
    for(i = 0; i < n; i++)
    {
        if(arr[i] != 0)
            printf("%d ", arr[i]);
    }
    
    return 0;
}