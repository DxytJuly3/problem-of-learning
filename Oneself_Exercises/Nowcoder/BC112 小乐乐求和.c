#include <stdio.h>
//阶乘
int main()
{
    long long n = 0;
    long long sum = 0;
    scanf("%lld", &n);
    for(int i = 1; i <= n; i++)
    {
        sum += i;
    }
    printf("%lld", sum);
    
    return 0;
}