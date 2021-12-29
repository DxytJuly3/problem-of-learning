//给你一个整数 n 。如果 n 恰好有三个正除数 ，返回 true ；否则，返回 false 。
//如果存在整数 k ，满足 n = k * m ，那么整数 m 就是 n 的一个 除数 。

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/three-divisors

bool isThree(int n)
{
    int count = 0;
    for(int i = 1; i <= n; i++)
    {
        if(n % i == 0)
            count++;
        if(count > 3)
            break;
    }
    if(count == 3)
        return true;
    else
        return false;
}