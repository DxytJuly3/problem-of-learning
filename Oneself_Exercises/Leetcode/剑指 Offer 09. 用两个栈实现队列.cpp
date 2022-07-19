/*
用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead
分别完成在队列尾部插入整数和在队列头部删除整数的功能(若队列中没有元素，deleteHead 操作返回 -1 )

示例 1：
输入：
["CQueue","appendTail","deleteHead","deleteHead"]
[[],[3],[],[]]
输出：[null,null,3,-1]

示例 2：
输入：
["CQueue","deleteHead","appendTail","appendTail","deleteHead","deleteHead"]
[[],[],[5],[2],[],[]]
输出：[null,-1,null,null,5,2]

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/yong-liang-ge-zhan-shi-xian-dui-lie-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*
题目思路：
题目只要求双栈实现队列 的 入队列(尾插) 和 出队列(头删)
既然是队列，按照要求就只能尾插、头删，且不能访问队尾元素外的其他元素
所以只需要保持，取队尾元素时，是新入队的元素；
最简单的思路是：
    两个栈，一个栈恒保持空 _meptyStack，另一个栈恒存储数据 _dataStack，入队列恒入进 _dataStack
    出队列则 将 _dataStack 数据 从队尾到队头 誊到 _meptyStack
    然后 _meptyStack 的队尾元素即为本次出队列元素，即 原 _dataStack队头元素
    然后保存并删除 _meptyStack 的队尾元素, 再将 _meptyStack 数据 从队尾到队头 誊到  _dataStack
    保持 数据栈存储数据 即可

优化版的思路：
    两个栈，一个栈只用来入队列用 _inStack，且只用其入队列，另一个队列称为 _outStack
    出队列时，若 _outStack 为空，且 _inStack 为空时，表示队列为空，返回 -1
    若 _outStack 为空，且 _inStack 不为空时，将_inStack所有数据出栈且挪入 _outStack 中
    若 _outStack 不为空，或 _inStack所有数据已经挪入 _outStack 中，则 保存_outStack 栈顶元素并出栈
    最后返回 保存的元素即可

    为什么可以这样写？  理解此写法最好画两个栈进行理解
    首先了解，队列 是先进先出的，且只能访问队尾元素，这是队列的规则、规范
    而题目要求 实现其先进先出的两个接口：尾插 和 头删
    尾插的实现非常简单，只对 _inStack 尾插
    而 头删就有一定的意思了
    当 _outStack 为空时，即表示要么数据全在 _inStack里，要么没有数据，_inStack没有数据就说明 队列为空
    若 _inStack 有数据，可以将其数据出栈并全倒叙存储到 _outStack 里，这样一来 队列头删数据，即为 _outStack栈的尾删数据

    当 _outStack 不为空时，即表示可以直接对 _outStack 尾删来达到 队列头删的功能
    为什么？ 举一个简单的例子：
    _inStack 存放有 1   4   9   5   7   2   7,尾删时，将数据存入 _outStack
    _outStack 变为  7   2   7   5   9   4   1, 此时_outStack栈顶元素 即为 _inStack的栈底元素
    直接对 _outStack 出栈操作，即为对 队列的头删操作
    _outStack 出栈后变为:   7   2   7   5   9   4
    下次 队列头删，_outStack 不为空，直接_outStack 出栈就可以了
    在 _outStack 为空之前，都对_outStack 直接出栈
    为空时 重复判断 _inStack 是否为空，可以保持模拟 队列的尾插 和 头删
*/

class CQueue
{
public:
    CQueue()
    {}
    
    void appendTail(int value)
    {
        // 简单思路
        //_dataStack.push(value);

        // 优化思路
        _inStack.push(value);
    }
    
    int deleteHead()
    {
        /*  简单思路：
        if(_dataStack.empty())
            return -1;
        
        while(!_dataStack.empty())
        {
            _emStack.push(_dataStack.top());
            _dataStack.pop();
        }
        int data_pop = _emStack.top();
        _emStack.pop();

        while(!_emStack.empty())
        {
            _dataStack.push(_emStack.top());
            _emStack.pop();
        }*/

        //优化思路：
        if(_outStack.empty())
        {
            if(_inStack.empty())
            {
                return -1;
            }
            while(!_inStack.empty())
            {
                _outStack.push(_inStack.top());
                _inStack.pop();
            }
        }

        int data_pop = _outStack.top();
        _outStack.pop();

        return data_pop;
    }
protected:
    /*  简单思路
    stack<int> _emStack;
    stack<int> _dataStack;
    */

    // 优化思路：
    stack<int> _inStack;
    stack<int> _outStack;
};

/**
 * Your CQueue object will be instantiated and called as such:
 * CQueue* obj = new CQueue();
 * obj->appendTail(value);
 * int param_2 = obj->deleteHead();
 */