//对于一个 正整数，如果它和除了它自身以外的所有 正因子 之和相等，我们称它为 「完美数」。
//给定一个 整数 n， 如果是完美数，返回 true，否则返回 false

//来源：力扣（LeetCode）
//链接：https://leetcode-cn.com/problems/perfect-number

bool checkPerfectNumber(int num)
{//没啥优化解法
    int sum = 0;
    for(int i = 2; i <= sqrt(num); i++)
    {
        if(num % i == 0)
        {
            sum += (i + num / i);
        }
    }
    if(num == 1 || num == 2)
        return false;
    else
    {
        if (sum + 1 == num)
            return true;
        else 
            return false;
    }
}