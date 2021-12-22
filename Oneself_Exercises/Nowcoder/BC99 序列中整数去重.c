#include <stdio.h>
//输入n个整数的序列，要求对这个序列进行去重操作。所谓去重，是指对这个序列中每个重复出现的整数，只保留该数第一次出现的位置，删除其余位置。
int main()
{
    int arr[1000] = { 0 };
    int i = 0;
    int n = 0;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        int tmp = 0;
        int flag = 0;
        scanf("%d", &tmp);
        for (int j = 0; j < i; j++)
        {
            if (tmp == arr[j])
                flag++;
        }
        if (flag == 0)
            arr[i] = tmp;
    }
    for (i = 0; i < n; i++)
    {
        if (arr[i] != 0)
            printf("%d ", arr[i]);
    }

    return 0;
}