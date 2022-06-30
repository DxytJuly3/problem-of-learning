/*
给你一个字符串 s ，根据下述规则反转字符串：
    所有非英文字母保留在原有位置。
    所有英文字母（小写或大写）位置反转。
返回反转后的 s 。

示例 1：
输入：s = "ab-cd"
输出："dc-ba"

示例 2：
输入：s = "a-bC-dEf-ghIj"
输出："j-Ih-gfE-dCba"

示例 3：
输入：s = "Test1ng-Leet=code-Q!"
输出："Qedo1ct-eeLg=ntse-T!"

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/reverse-only-letters
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    bool isLetter(char& c)
    {
        if('a' <= c && c <= 'z')
            return true;
        else if('A' <= c && c <= 'Z')
            return true;
        else
            return false;
    }
    string reverseOnlyLetters(string s)
    {
        // 迭代器方法(首次接触迭代器 就用了)
        string::iterator leftIt = s.begin();
        string::iterator rightIt = s.end()-1;
        while(leftIt < rightIt)
        {
            while(leftIt < rightIt && !isLetter(*leftIt))
                leftIt++;
            while(leftIt < rightIt && !isLetter(*rightIt))
                rightIt--;

            swap(*leftIt++, *rightIt--);
        }

        return s;
    }
};