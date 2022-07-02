/*
给定一个字符串 s ，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。

示例 1：
输入：s = "Let's take LeetCode contest"
输出："s'teL ekat edoCteeL tsetnoc"

示例 2:
输入： s = "God Ding"
输出："doG gniD"

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/reverse-words-in-a-string-iii
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    void reverseString(string& s, size_t left, size_t right)
    {
        for(; left < right; left++, right--)
            swap(s[left], s[right]);
    }
    string reverseWords(string s)
    {
        int _pos = 0;
        int begin = 0;
        while((_pos = s.find(' ', _pos)) != string::npos)
        {
            reverseString(s, begin, _pos - 1);
            begin = ++_pos;
        }
        reverseString(s, begin, s.size() - 1);

        return s;
    }
};