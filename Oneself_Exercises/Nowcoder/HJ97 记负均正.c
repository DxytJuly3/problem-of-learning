//首先输入要输入的整数个数n，然后输入n个整数。输出为n个整数中负数的个数，和所有正整数的平均值，结果保留一位小数。
//0即不是正整数，也不是负数，不计入计算

#include <stdio.h>

int main()
{
    int n = 0;
    while(scanf("%d", &n) != EOF)
    {
        int arr[2002] = { 0 };
        int pos_sum = 0;
        int count_neg = 0;
        int count_pos = 0;
        for(int i = 0; i < n; i++)
        {
            scanf("%d", &arr[i]);
            if (arr[i] < 0)
                count_neg++;
            else if (arr[i] > 0)
            {
                count_pos++;
                pos_sum += arr[i];
            }
        }
        printf("%d %.1lf\n", count_neg, (double)pos_sum / count_pos);
    }
    
    return 0;
}