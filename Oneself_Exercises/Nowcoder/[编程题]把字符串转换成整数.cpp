/*
链接：https://www.nowcoder.com/questionTerminal/1277c681251b4372bdef344468e4f26e
来源：牛客网

将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。 数值为 0 或者字符串不是一个合法的数值则返回 0
数据范围：字符串长度满足 0≤n≤100 0 \le n \le 100 \ 0≤n≤100 
进阶：空间复杂度 O(1) O(1) \ O(1)  ，时间复杂度 O(n) O(n) \ O(n) 

注意：
①字符串中可能出现任意符号，出现除 +/- 以外符号时直接输出 0
②字符串中可能出现 +/- 且仅可能出现在字符串首位。

输入描述:
输入一个字符串,包括数字字母符号,可以为空

输出描述:
如果是合法的数值表达则返回该数字，否则返回0

示例1
输入
"+2147483647"
输出
2147483647

示例2
输入
"1a33"
输出
0
*/
class Solution {
public:
    int StrToInt(string str) {
        if(str.empty())
            return 0;
        for(auto c : str){
            if(c != '+' && c != '-' && (c > '9' || c < '0'))
                return 0;
        }
         
        int ret = 0;
        int power = 0;
        auto digit = str.rbegin();
        if(*str.begin() <= '9' && *str.begin() >= '0') {
            while(digit != str.rend()) {
                ret += (*digit - '0')*pow(10, power);
                digit++;
                power++;
            }
        }
        else {
            while(digit != str.rend()-1) {
                ret += (*digit - '0')*pow(10, power);
                digit++;
                power++;
            }
        }
         
        if(*str.begin() != '-')
            return ret;
        else
            return 0-ret;
    }
};