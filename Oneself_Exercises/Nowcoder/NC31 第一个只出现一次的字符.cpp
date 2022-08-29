/*
描述
在一个长为 字符串中找到第一个只出现一次的字符,并返回它的位置, 如果没有则返回 -1（需要区分大小写）.（从0开始计数）
数据范围：0≤n≤100000 \le n \le 100000≤n≤10000，且字符串只有字母组成。
要求：空间复杂度 O(n)O(n)O(n)，时间复杂度 O(n)O(n)O(n)
示例1
输入：
"google"
返回值：
4

示例2
输入：
"aa"
返回值：
-1

来源：牛客（Nowcoder）
链接：https://www.nowcoder.com/practice/1c82e8cf713b4bbeb2a5b31cf5b0417c
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
C++ 思路很简单
使用map<char, int> 来统计出现的字符以及出现的次数

遍历 两遍字符串：
    第一遍 在map中 统计出现的字符 和 字符出现的次数
    第二遍，找第一个出现次数为1的字符，找到就返回字符的int，找不到返回-1
*/
class Solution {
public:
    int FirstNotRepeatingChar(string str) {
        map<char, int> strMap;
        
        // map中统计字符
        for(int i = 0; i < str.size(); i++) 
            strMap[str[i]]++;
        // 找第一个出现一次的字符
        for(int i = 0; i < str.size(); i++) {
            if(strMap[str[i]] == 1)
                return i;
        }
        
        return -1; 
    } 
};