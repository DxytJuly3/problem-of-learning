/*
541. 反转字符串 II
给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k 字符中的前 k 个字符。
    如果剩余字符少于 k 个，则将剩余字符全部反转。
    如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。

示例 1：
输入：s = "abcdefg", k = 2
输出："bacdfeg"

示例 2：
输入：s = "abcd", k = 2
输出："bacd"

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/reverse-string-ii/
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    void reverseString(string& s, size_t left, size_t right)
    {
        for(; left < right; left++, right--)
            swap(s[left], s[right]);
    }
    string reverseStr(string s, int k)
    {
        size_t begin = 0;
        for(int i = 0; i < s.size(); i += 2*k)
        {
            reverseString(s, begin + i, (begin + i + k < s.size()) ? (begin + i + k - 1) : s.size() - 1);
        }

        return s;
    }
};