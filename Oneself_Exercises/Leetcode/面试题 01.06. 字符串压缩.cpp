/*
字符串压缩。利用字符重复出现的次数，编写一种方法，实现基本的字符串压缩功能。比如，字符串aabcccccaaa会变为a2b1c5a3。
若“压缩”后的字符串没有变短，则返回原先的字符串。你可以假设字符串中只包含大小写英文字母（a至z）。

示例1:
 输入："aabcccccaaa"
 输出："a2b1c5a3"

示例2:
 输入："abbccd"
 输出："abbccd"
 解释："abbccd"压缩后为"a1b2c2d1"，比原字符串长度更长。

提示：
    字符串长度在[0, 50000]范围内。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/compress-string-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
思路分析:
    定义一个 string ret, 和字母的计数letterCount 并初始化为1
    遍历原字符串, 并对比 S[i] 和  S[i+1], 如果不相等 则在 ret 中尾插 S[i] 和 letterCount的字符形式
    并将letterCount 置 0； 遍历过程中 letterCount ++
    然后当 ret的size 小于 原字符串的size时 , 返回 ret就可以了
    不然 返回 原字符串
*/

class Solution {
public:
    string compressString(string S) {
        string ret;
        int letterCount = 1;
        for(int i = 0; i < S.size(); i++) {
            if(S[i] != S[i+1]) {
                ret += S[i];
                ret += to_string(letterCount);
                letterCount = 0;
            }
            letterCount++;
        }

        return ret.size() < S.size() ? ret : S;
    }
};