//完全数（Perfect number），又称完美数或完备数，是一些特殊的自然数。
//它所有的真因子（即除了自身以外的约数）的和（即因子函数），恰好等于它本身。
//例如：28，它有约数1、2、4、7、14、28，除去它本身28外，其余5个数相加，1+2+4+7+14=28。
//输入n，请输出n以内(含n)完全数的个数。

#include <stdio.h>
#include <math.h>

int main()
{
    int n = 0;
    while (scanf("%d", &n) != EOF)
    {
        int count = 0;
        for (int i = 2; i <= n; i++)
        {
            int sum = 0;
            for (int j = 1; j <= sqrt(i); j++)
            {
                if (i % j == 0)
                    sum += (j + i / j);
            }
            if (sum - i == i)
                count++;
        }
        printf("%d\n", count);
    }

    return 0;
}