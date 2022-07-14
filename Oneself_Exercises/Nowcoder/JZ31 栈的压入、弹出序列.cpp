/*
描述
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。
假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列
但4,3,5,1,2就不可能是该压栈序列的弹出序列。
1. 0<=pushV.length == popV.length <=1000
2. -1000<=pushV[i]<=1000
3. pushV 的所有数字均不相同

示例1
输入：
[1,2,3,4,5],[4,5,3,2,1]
返回值：
true
说明：
可以通过push(1)=>push(2)=>push(3)=>push(4)=>pop()=>push(5)=>pop()=>pop()=>pop()=>pop()
这样的顺序得到[4,5,3,2,1]这个序列，返回true      

示例2
输入：
[1,2,3,4,5],[4,3,5,1,2]
返回值：
false
说明：
由于是[1,2,3,4,5]的压入顺序，[4,3,5,1,2]的弹出顺序，要求4，3，5必须在1，2前压入，且1，2不能弹出
但是这样压入的顺序，1又不能在2之前弹出，所以无法形成的，返回false

链接：https://www.nowcoder.com/practice/d77d11405cc7470d82554cb392585106
*/

class Solution
{
public:
    // 具体思路就是：
    // 建立一个栈，遍历 pushV 按照顺序入栈
    // 遍历入栈的过程中，需要用栈顶数据与 popV中的数据从头开始对比，且需要循环对比
    // 如果栈顶数据与当前指向的popV中的数据相等，出栈且 对比popV数据位置向后移
    // 如果不相等，进入下次压栈
    // 遍历压栈结束后，如果 栈为空即为指定的出栈顺序合法
    //
    bool IsPopOrder(vector<int> pushV,vector<int> popV)
    {
        stack<int> st;
        vector<int>::iterator vit = popV.begin();
        for(auto elem : pushV)
        {
            st.push(elem);
            while(!st.empty() && st.top() == *vit)
            {
                st.pop();
                vit++;
            }
        }
       
        return st.empty();
    }
};