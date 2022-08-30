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
    //  本题有一种位运算的思路：
    //      26个小写字母，每个字母是否出现过 可以用0、1表示
    //      看到 0、1 不难想到二进制
    //      本题就可以使用int类型数据的二进制位来解决，int 是32位的，26个小写英文字母只需要26位就可以了
    //      位运算的思路就是：
    //          a-z 分别用 1 2 4 8等表示
    //          a-z 是否出现过，分别映射为 int数据的二进制位，比如 a出现过，最后一位为1，未出现过则为0
    //          每个小写字母都可以映射到 int数据的二进制位上
    //          判断当前字母是否出现过时，若表示当前字母的映射位已经为 1，则表示次字母已经出现过了，返回false
    //          遍历完字符串之后，没有遇到映射位已经为 1的情况，就返回true
    bool isUnique(string astr) {
        if(astr.empty())
            return true;
        if(astr.size() > 26)
            return false;

        int bitMap = 0;     // 作为映射字母是否出现过的变量

        // 一个数 & 一个只有某一二进制位为 1 的数，如果结果大于0 就表示这个数的那个二进制位为 1
        for(int i = 0; i < astr.size(); i++) {
            if(bitMap & (1 << (astr[i] - 'a')))
                return false;
            
            bitMap |= 1 << (astr[i] - 'a');
        }

        return true;
    }
};