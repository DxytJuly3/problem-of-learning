#include <stdio.h>
//输入10个整数，分别统计输出正数、负数的个数。
int main()
{
    int arr[10] = { 0 };
    int i = 0;
    int positive = 0;
    int negative = 0;
    for(i = 0; i < 10; i++)
    {
        scanf("%d", &arr[i]);
    }
    for(i = 0; i < 10; i++)
    {
        if(arr[i] > 0)
            positive++;
        else if(arr[i] < 0)
            negative++;
    }
    printf("positive:%d\nnegative:%d", positive, negative);
    
    return 0;
}