/*
给定一个字符串，编写一个函数判定其是否为某个回文串的排列之一。
回文串是指正反两个方向都一样的单词或短语。排列是指字母的重新排列。
回文串不一定是字典当中的单词

示例1:
输入："tactcoa"
输出：true（排列有"tacocat"、"atcocta"，等等）

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/palindrome-permutation-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
/*
思路1：
    可以 统计各个字符出现的次数，出现偶数次计0，出现技术次计1
    最后 应该只有 1个字符 或 没有字符出现偶数次
*/

class Solution {
public:
    bool canPermutePalindrome(string s) {
        if(s.empty())
            return true;

        map<char, int> mapS;
        size_t count = 0;
        for(int i = 0; i < s.size(); i++) {
            if(mapS[s[i]] == 0)
                mapS[s[i]] = 1;
            else
                mapS[s[i]] = 0;
        }
        for(int i = 0;i < mapS.size(); i++) {
            count += mapS[i];
        }
        if(count == 1 || count == 0)
            return true;
        else
            return false;
    }
};