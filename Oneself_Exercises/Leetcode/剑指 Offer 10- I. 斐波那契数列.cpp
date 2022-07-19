/*
写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项（即 F(N)）。斐波那契数列的定义如下：
F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。
答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

示例 1：
输入：n = 2
输出：1

示例 2：
输入：n = 5
输出：5

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/fei-bo-na-qi-shu-lie-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
题目思路：
    简单的思路：
    就 记录i位置 的前两个位置的数据，然后 相加%1000000007 在赋于i  i就是i位置的斐波那契数
*/

class Solution
{
public:
    int fib(int n)
    {
        if (n < 2)
        {
            return n;
        }

        int fib_N = 0;
        int fib_0 = 0;      // 表示当前数的前两位
        int fib_1 = 1;      // 表示当前数的前一位
        for(int i = 2; i <= n; i++)
        {
            fib_N = (fib_0 + fib_1)%1000000007;
            fib_0 = fib_1;
            fib_1 = fib_N;
        }

        return fib_N;
    }
};