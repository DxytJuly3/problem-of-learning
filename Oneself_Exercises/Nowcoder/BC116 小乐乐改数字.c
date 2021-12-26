#include <stdio.h>
#include <math.h>
//小乐乐喜欢数字，尤其喜欢0和1。他现在得到了一个数，想把每位的数变成0或1。
//如果某一位是奇数，就把它变成1，如果是偶数，那么就把它变成0。请你回答他最后得到的数是多少。
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