/*
给定一个字符串 s ，找到 它的第一个不重复的字符，并返回它的索引 。如果不存在，则返回 -1 。
示例 1：
输入: s = "leetcode"
输出: 0

示例 2:
输入: s = "loveleetcode"
输出: 2

示例 3:
输入: s = "aabb"
输出: -1

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/first-unique-character-in-a-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    int firstUniqChar(string s)
    {
        int count_s[26] = {0};
        for(int i = 0; i < s.size(); i++)
        {
            int x = s[i] - 'a';
            count_s[x]++;
        }
        for(int i = 0; i < s.size(); i++)
        {
            int x = s[i] - 'a';
            if(count_s[x] == 1)
            {
                return i;
            }
        }

        return -1;
    }
};