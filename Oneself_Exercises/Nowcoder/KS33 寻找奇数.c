//现在有一个长度为 n 的正整数序列，其中只有一种数值出现了奇数次，其他数值均出现偶数次，请你找出那个出现奇数次的数值。

#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void* x, const void* y)
{
    return *(int*)x - *(int*)y;
}

int main()
{
    int n = 0;
    scanf("%d", &n);
    int* arr = (int*)malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++)
    {
       scanf("%d", arr + i);
    }
    if(n == 1)
    {
        printf("%d\n", *arr);
        return 0;
    }
    else
    {
        qsort(arr, n, sizeof(arr[0]), cmp_int);
        for(int i = 0; i < n; i += 2)
        {
            if(arr[i] != arr[i + 1])
            {
                printf("%d\n", arr[i]);
                return 0;
            }
        }
    }
}