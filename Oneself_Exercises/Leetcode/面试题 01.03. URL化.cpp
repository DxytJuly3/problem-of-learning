/*
URL化。编写一种方法，将字符串中的空格全部替换为%20。假定该字符串尾部有足够的空间存放新增字符，并且知道字符串的“真实”长度。
（注：用Java实现的话，请使用字符数组实现，以便直接在数组上操作。）

示例 1：
输入："Mr John Smith    ", 13
输出："Mr%20John%20Smith"

示例 2：
输入："               ", 5
输出："%20%20%20%20%20"

提示：
    字符串长度在 [0, 500000] 范围内。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/string-to-url-lcci
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
题意分析：
    给定字符串的实际长度, 且不用考虑扩容, 将字符串实际长度中的' ' 转换成 "%20"
思路分析：
    思路1：
        
    思路2：
        定义一个string ret, 遍历原字符串 并将其尾插至 ret 中, 遍历遇到' ' 则在ret中尾插 "%20" 直到遍历结束
*/

class Solution {
public:
    string replaceSpaces(string S, int length) {
        string ret;
        for(int i = 0; i < length; i++) {
            if(S[i] != ' ') {
                ret += S[i];
            }
            else {
                ret += "%20"; 
            }
        }

        return ret;
    }
};