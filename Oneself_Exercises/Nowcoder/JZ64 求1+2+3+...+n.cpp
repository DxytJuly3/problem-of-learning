/*
描述
求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。

数据范围： 0<n≤200
进阶： 空间复杂度 O(1) ，时间复杂度 O(n)

原题链接：https://www.nowcoder.com/practice/7a0da8fc483247ff8800059e12d7caf1
*/

class Solution 
{
public:
    class Sum
    {
    public:
        Sum()
        {
            _ret += _n;
            _n++;
        }
    };
    int Sum_Solution(int n)
    {
        Sum* ps = new Sum[n];
        
        return _ret;
    }
private:
    static int _n;
    static int _ret;
};

int Solution::_n = 1;
int Solution::_ret = 0;