/*
实现一个算法，确定一个字符串 s 的所有字符是否全都不同。
示例 1：
输入: s = "leetcode"
输出: false 

示例 2：
输入: s = "abc"
输出: true
限制：
    0 <= len(s) <= 100
    s[i]仅包含小写字母
    如果你不使用额外的数据结构，会很加分。

来源：力扣（Leetcode）
链接：https://leetcode.cn/problems/is-unique-lcci/
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    // 题目已经要求 字符串s仅包含小写字母，即表示 字符全都不同的字符串最多26位

    // 思路简单 使用 map的方法：
    // 用map<cahr, int>来统计字符及出现次数
    // 然后判断 有没有出现次数不是 1 次的字符
    /*bool isUnique(string astr) {
        if(astr.empty())
            return true;
        if(astr.size > 26)
            return false;

        map<char, int> strMap;
        // map中统计字符
        for(int i = 0; i < astr.size(); i++) 
            strMap[astr[i]]++;
        // 找第一个出现一次的字符
        for(int i = 0; i < astr.size(); i++) {
            if(strMap[astr[i]] != 1)
                return false;
        }
        
        return true;
    }*/

    // 不使用额外的数据结构的方法1：
    // 先排序，在相邻对比
    /*bool isUnique(string astr) {
        if(astr.empty())
            return true;
        if(astr.size > 26)
            return false;

        sort(astr.begin(),astr.end());
        for(int i = 0; i < astr.size() - 1; i++)
            if(astr[i] == astr[i+1])
                return false;
        
        return true;
    }*/

    // 不使用额外的数据结构的方法2：
    // 
    bool isUnique(string astr) {
        if(astr.empty())
            return true;
        if(astr.size > 26)
            return false;

        
    }
};