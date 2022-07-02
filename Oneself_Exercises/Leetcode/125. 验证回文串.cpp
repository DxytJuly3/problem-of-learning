/*
给定一个字符串，验证它是否是回文串，只考虑字母和数字字符，可以忽略字母的大小写。
说明：本题中，我们将空字符串定义为有效的回文串。

示例 1:
输入: "A man, a plan, a canal: Panama"
输出: true
解释："amanaplanacanalpanama" 是回文串

示例 2:
输入: "race a car"
输出: false
解释："raceacar" 不是回文串

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/valid-palindrome
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    bool isPalindrome(string s)
    {
        if(s.empty())
            return true;
        else
        {
            string newS;
            string::iterator sIt = s.begin();
            while(sIt < s.end())
            {
                if((*sIt <= 'z' && *sIt >= 'a')
                || (*sIt <= 'Z' && *sIt >= 'A')
                || (*sIt <= '9' && *sIt >= '0'))
                {
                    if(*sIt <= 'Z' && *sIt >= 'A')
                    {
                        newS += *sIt + 32;
                    }
                    else
                    {
                        newS += *sIt;
                    }
                }
                sIt++;
            }

            string::iterator nsItb = newS.begin();
            string::iterator nsIte = newS.end();
            while(nsItb < nsIte)
            {
                if(*nsItb == *(nsIte-1))
                {
                    nsItb++;
                    nsIte--;
                    continue;
                }
                else
                    return false;
            }
        }
        return true;
    }
};