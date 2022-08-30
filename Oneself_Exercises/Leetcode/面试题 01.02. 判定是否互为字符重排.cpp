/*
给定两个字符串 s1 和 s2，请编写一个程序，确定其中一个字符串的字符重新排列后，能否变成另一个字符串。

示例 1：
输入: s1 = "abc", s2 = "bca"
输出: true 

示例 2：
输入: s1 = "abc", s2 = "bad"
输出: false

说明：
    0 <= len(s1) <= 100
    0 <= len(s2) <= 100 

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/check-permutation-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
本题有几个思路
    1. 排序之后对比内容是否相同
    2. 统计各个字符出现的次数，然后比较
        此思路可以有多种写法，可以直接用map，也可以哈希思想用其他数据结构映射
*/

class Solution {
public:
    // 排序 + 对比内容
    /*bool CheckPermutation(string s1, string s2) {
        if(s1.size() != s2.size())
            return false;

        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());

        return s1 == s2;
    }*/

    // map统计字符出现次数
    bool CheckPermutation(string s1, string s2) {
        if(s1.size() != s2.size())
            return false;

        map<char, int> mapS1;
        map<char, int> mapS2;
        for(int i = 0; i < s1.size(); i++) {
            mapS1[s1[i]]++;
        }
        for(int i = 0; i < s2.size(); i++) {
            mapS2[s2[i]]++;
        }

        return mapS1 == mapS2;
    }
};