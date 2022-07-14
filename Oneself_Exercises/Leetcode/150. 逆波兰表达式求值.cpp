/*
根据 逆波兰表示法，求表达式的值。
有效的算符包括 +、-、*、/ 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。
注意 两个整数之间的除法只保留整数部分。
可以保证给定的逆波兰表达式总是有效的。换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。

示例 1：
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9

示例 2：
输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6

示例 3：
输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/evaluate-reverse-polish-notation
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution
{
public:
    // 具体思路是：
    // 遍历 vector，遇到数字将其入栈，遇到运算符，取栈顶两个数据并通过运算符运算
    // 
    int evalRPN(vector<string>& tokens)
    {
        stack<int> st;
        for(const auto& ch : tokens)
        {
            if(ch == "+" || ch == "-" || ch == "*" || ch == "/")
            {
                int right = st.top();        // 先取出来的作为运算符右操作数，因为左操作数进栈的早
                st.pop();
                int left = st.top();
                st.pop();

                switch(ch[0])
                {
                    case '+':
                        st.push(left + right);
                        break;
                    case '-':
                        st.push(left - right);
                        break;
                    case '*':
                        st.push(left * right);
                        break;
                    case '/':
                        st.push(left / right);
                        break;
                    default:
                        break;
                }
            }
            else
            {
                st.push(stoi(ch));
            }
        }

        return st.top();
    }
};