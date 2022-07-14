/*
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

示例 1：
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]

示例 2：
输入：digits = ""
输出：[]

示例 3：
输入：digits = "2"
输出：["a","b","c"]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/letter-combinations-of-a-phone-number
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution
{
    string _numToStr[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
public:
    void _letterCombine(string digits, size_t di, string combineStr, vector<string>& retV)
    {
        if(di == digits.size())
        {
            retV.push_back(combineStr);
            return ;
        }

        size_t num = digits[di] - '0';
        string _letterStr = _numToStr[num];

        for(auto ch : _letterStr)
        {
            _letterCombine(digits, di + 1, combineStr + ch, retV);
        }
    }
    vector<string> letterCombinations(string digits)
    {
        vector<string> retV;
        if(digits.empty())
            return retV;

        size_t i = 0;
        string Str;
        _letterCombine(digits, i, Str, retV);

        return retV;
    }
};