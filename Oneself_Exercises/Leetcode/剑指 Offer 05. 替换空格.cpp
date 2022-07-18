/*
请实现一个函数，把字符串 s 中的每个空格替换成"%20"。

示例 1：
输入：s = "We are happy."
输出："We%20are%20happy."

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/ti-huan-kong-ge-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
本题 用C++ 写的话
细节在于，string类是有容量的，且每次替换 size都会+2，很可能导致容量满
且，最好不要在替换的过程中增容，因为增容会导致迭代器失效问题
所以 可以提前统计一遍 ' ' 的个数，先扩容再遍历替换
*/
class Solution
{
public:
    string replaceSpace(string s)
    {
        size_t count = 0;
        for(char c : s)
        {
            if(c == ' ')
                count++;
        }
        s.reserve(s.capacity() + 2 * count);

        string::iterator sit = s.begin();
        while(sit < s.end())
        {
            if(*sit == ' ')
            {
                s.replace(sit-s.begin(), 1, "%20");
            }
            sit++;
        }

        return s;
    }
};