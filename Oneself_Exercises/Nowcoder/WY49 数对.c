//牛牛以前在老师那里得到了一个正整数数对(x, y), 牛牛忘记他们具体是多少了。
//但是牛牛记得老师告诉过他x和y均不大于n, 并且x除以y的余数大于等于k。
//牛牛希望你能帮他计算一共有多少个可能的数对。

#include <stdio.h>

int main()
{
    long n, k;
    while(~scanf("%ld %ld", &n, &k))
    {
        if (k == 0)
        {
            printf("%ld\n", n * n);
            continue;
        }
        long count = 0;
        for(long y = k + 1; y <= n; y++)
        {
            count += ((n / y) * (y - k)) + ((n % y < k) ? 0 : (n % y - k + 1));
        }
        printf("%ld\n", count);
    }
    
    return 0;
}

