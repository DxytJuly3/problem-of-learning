/*
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
实现 MinStack 类:
    MinStack() 初始化堆栈对象。
    void push(int val) 将元素val推入堆栈。
    void pop() 删除堆栈顶部的元素。
    int top() 获取堆栈顶部的元素。
    int getMin() 获取堆栈中的最小元素。

示例 1:
输入：
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]
输出：
[null,null,null,null,-3,null,0,-2]

解释：
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> 返回 -3.
minStack.pop();
minStack.top();      --> 返回 0.
minStack.getMin();   --> 返回 -2.

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/min-stack
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。*/
/*
具体思路：
类成员两个栈，一个正常入栈存放数据 _dataStack不做初始化，另一个栈 存当前最小值 _minStack每个空间初始化为 INT_MAX
当_dataStack 压栈时，判断压入的数据是否 <= _minStack栈顶元素，是则 也罢数据压入 _minStack中
当_dataStack 出栈时，判断即将出栈的数据(即_dataStack.top())是否 <= _minStack栈顶元素，是，则 _minStack 也出栈
即 保持 _minStack的栈顶元素 为 _dataStack中数据的最小值
*/

class MinStack
{
public:
    MinStack()
    {
        _minStack.push(INT_MAX);
    }
    
    void push(int val)
    {
        _dataStack.push(val);
        if(val <= _minStack.top())
        {
            _minStack.push(val);
        }
    }
    
    void pop()
    {
        if(_dataStack.top() <= _minStack.top())
        {
            _minStack.pop();
        }
        _dataStack.pop();
    }
    
    int top()
    {
        return _dataStack.top();
    }
    
    int getMin()
    {
        return _minStack.top();
    }
private:
    stack<int> _minStack;
    stack<int> _dataStack;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */