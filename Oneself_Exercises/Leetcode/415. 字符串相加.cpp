/* 
给定两个字符串形式的非负整数 num1 和num2 ，计算它们的和并同样以字符串形式返回。
你不能使用任何內建的用于处理大整数的库（比如 BigInteger）， 也不能直接将输入的字符串转换为整数形式

示例 1：
输入：num1 = "11", num2 = "123"
输出："134"

示例 2：
输入：num1 = "456", num2 = "77"
输出："533"

示例 3：
输入：num1 = "0", num2 = "0"
输出："0"

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/add-strings
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    string addStrings(string num1, string num2)
    {
        int end1 = num1.size() - 1;
        int end2 = num2.size() - 1;
        int carry = 0;
        
        string ret;
        int sum = 0;
        while(end1 >= 0 || end2 >= 0)
        {
            int val1 = end1 >= 0 ? num1[end1] - '0' : 0;
            int val2 = end2 >= 0 ? num2[end2] - '0' : 0;
            sum = val1 + val2 + carry;
            carry = 0;
            if(sum >= 10)
            {
                sum -= 10;
                carry = 1;
            }
            ret += sum + '0';
            end1--;
            end2--;
        }
        if(carry)
            ret += '1';
        reverse(ret.begin(), ret.end());

        return ret;
    }
};