/*
描述
将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。 数值为 0 或者字符串不是一个合法的数值则返回 0
数据范围：字符串长度满足 0≤n≤100 
进阶：空间复杂度 O(1) ，时间复杂度 O(n) 
注意：
①字符串中可能出现任意符号，出现除 +/- 以外符号时直接输出 0
②字符串中可能出现 +/- 且仅可能出现在字符串首位。
输入描述：
输入一个字符串,包括数字字母符号,可以为空
返回值描述：
如果是合法的数值表达则返回该数字，否则返回0
示例1
输入：
"+2147483647"
返回值：
2147483647

示例2
输入：
"1a33"
返回值：
0

链接：https://www.nowcoder.com/practice/1277c681251b4372bdef344468e4f26e
*/

class Solution {
public:
    int StrToInt(string str)
    {
        long long ret = 0;
        int flag = 1;
        for(int i = 0; i < str.size(); i++)
        {
            if(str[i] == ' ' || str[i] == '+')
                continue;
            else if(str[i] == '-')
            {
                flag = -1;
                continue;
            }
            
            if(str[i] >= '0' && str[i] <= '9')
                ret = ret * 10 + (str[i] - '0');
            else
                return 0;
        }
        
        return flag * ret;
    }
};