#include <stdio.h>
//小乐乐最近在课上学习了如何求两个正整数的最大公约数与最小公倍数
//但是他竟然不会求两个正整数的最大公约数与最小公倍数之和，请你帮助他解决这个问题。
long long compute_gcd(long long n, long long m)
{
    if (m > n)
    {
        long long tmp = m;
        m = n;
        n = tmp;
    }
    while (n % m != 0)
    {
        int tmp = n % m;
        n = m;
        m = tmp;
    }
    return m;
}

int main()
{//gcd 最大公因数    lcm 最小公倍数
    long long n = 0;
    long long m = 0;
    scanf("%lld%lld", &n, &m);
    long long gcd = compute_gcd(n, m);
    long long lcm = n * m / gcd;            //两整数的乘积等于其最小公倍数和最大公因数的乘积
    long long sum_gcd_lcm = gcd + lcm;
    printf("%lld", sum_gcd_lcm);

    return 0;
}