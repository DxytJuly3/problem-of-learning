#include <stdio.h>
//有一个有序数字序列，从小到大排序，将一个新输入的数插入到序列中，保证插入新数后，序列仍然是升序。
//输入描述：
//共三行，
//第一行输入一个整数(0≤N≤50)。
//第二行输入N个升序排列的整数，输入用空格分隔的N个整数。
//第三行输入想要进行插入的一个整数。
//输出描述：
//输出为一行，N+1个有序排列的整数。
int main()
{
    int n = 0;
    int arr[50] = { 0 };
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
    }
    scanf("%d", &arr[0]);
    for (int j = 0; j < n; j++)
    {
        if (arr[j] > arr[j + 1])
        {
            int tmp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = tmp;
        }
        else
            break;
    }
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
