/*
请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
实现 MyQueue 类：
    void push(int x) 将元素 x 推到队列的末尾
    int pop() 从队列的开头移除并返回元素
    int peek() 返回队列开头的元素
    boolean empty() 如果队列为空，返回 true ；否则，返回 false
说明：
你只能使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size, 和 is empty 操作是合法的。
你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。

示例 1：
输入：
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 1, 1, false]
解释：
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/implement-queue-using-stacks
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class MyQueue {
public:
    MyQueue()
    {}
    void push(int x)
    {
        _pushST.push(x);
    }
    int pop()
    {
        size_t pstSize = _pushST.size();
        for(int i = 0; i < pstSize; i++)
        {
            _emptyST.push(_pushST.top());
            _pushST.pop();
        }
        int ret = _emptyST.top();
        _emptyST.pop();
        for(int i = 0; i < pstSize - 1; i++)
        {
            _pushST.push(_emptyST.top());
            _emptyST.pop();
        }

        return ret;
    }
    int peek()
    {
        size_t pstSize = _pushST.size();
        for(int i = 0; i < pstSize; i++)
        {
            _emptyST.push(_pushST.top());
            _pushST.pop();
            std::cout << i;
        }
        int ret = _emptyST.top();
        for(int i = 0; i < pstSize; i++)
        {
            _pushST.push(_emptyST.top());
            _emptyST.pop();
        }

        return ret;
    }
    bool empty()
    {
        return _pushST.empty();
    }

private:
    stack<int> _pushST;
    stack<int> _emptyST;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */