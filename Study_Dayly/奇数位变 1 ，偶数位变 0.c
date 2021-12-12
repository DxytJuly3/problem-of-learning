#include <stdio.h>
#include <math.h>
//奇数位变 1 ，偶数位变 0 
//并输出
int main()
{
    long long n = 0;
    int count = 0;
    scanf("%d", &n);
    int sum = 0;
    int flag = 0;
    while (n)
    {
        if (n % 10 % 2 != 0)
            flag = 1;
        else
            flag = 0;
        if (flag == 1)
            sum = sum + pow(10, count);
        count++;
        n /= 10;
    }
    printf("%d", sum);

    return 0;
}