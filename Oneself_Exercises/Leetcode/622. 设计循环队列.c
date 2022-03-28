/*
设计你的循环队列实现。 
循环队列是一种线性数据结构，其操作表现基于 FIFO（先进先出）原则并且队尾被连接在队首之后以形成一个循环。
它也被称为“环形缓冲器”。
循环队列的一个好处是我们可以利用这个队列之前用过的空间。
在一个普通队列里，一旦一个队列满了，我们就不能插入下一个元素，即使在队列前面仍有空间。
但是使用循环队列，我们能使用这些空间去存储新的值。
你的实现应该支持如下操作：

    MyCircularQueue(k): 构造器，设置队列长度为 k 。
    Front: 从队首获取元素。如果队列为空，返回 -1 。
    Rear: 获取队尾元素。如果队列为空，返回 -1 。
    enQueue(value): 向循环队列插入一个元素。如果成功插入则返回真。
    deQueue(): 从循环队列中删除一个元素。如果成功删除则返回真。
    isEmpty(): 检查循环队列是否为空。
    isFull(): 检查循环队列是否已满。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/design-circular-queue
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

/*数组实现 思路*/
/*
循环队列，需要两个变量来分别表示，队列的头(Front)(队中第一个元素)，队列的尾(Back)(队中最后一个元素)
但是，如果队列中所有空间都存放数据，没有一个标志性东西，就无法判断队列是否空或是否满
所以一般会保证队列中有一个空的空间，一般是最后一个元素的后一位空间
类似这样：https://dxyt-july-image.oss-cn-beijing.aliyuncs.com/leecode/622-CircularQueue/CircularQueue-Blank.png
这样可以保证不会出现 队列所有空间存放数据导致无法判断循环队列是否已满 ，无法判断就无法判断是否进行下个入队操作
所以，循环队列如果需要存储 k 个数据，就需要开辟 k+1 个空间
队尾(Back)的位置，一般处于循环队列最后一个数据的下一位(此位为空)(ps:上图为了方便理解将 Back 置于了最后一个元素上)
然后可以画图分析，
当 Front 位置 === Back 位置时候，循环队列为空
当 Front 位置 在 Back 位置的后一位，循环队列为满
但是，要注意数组模式的循环队列，数组的最后一个空间和数组的第一个空间物理空间上不是连续的，但是要保证循环效果，Front 和 Back 两个变量在数组的最后一个空间的时候，要单独考虑
*/
/*
typedef struct
{
    int* data;          // 存放数据的数组
    int front;          // 队列头位置变量
    int back;           // 队列尾位置变量
    int k;              // 存放数据空间的大小，真正开辟空间需要 +1
} MyCircularQueue;

bool myCircularQueueIsFull(MyCircularQueue* obj);
bool myCircularQueueIsEmpty(MyCircularQueue* obj);

MyCircularQueue* myCircularQueueCreate(int k)
{
    MyCircularQueue* obj = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    assert(obj);

    obj->data = (int*)malloc((k + 1) * sizeof(int));
    assert(obj);
    obj->front = obj->back = 0;
    obj->k = k;

    return obj;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value)
{   // 入队操作，如果成功返回 true，不成功返回 false
    assert(obj);

    if(myCircularQueueIsFull(obj))          // 如果循环队列为满，直接返回 false
        return false;

    // 循环队列不满
    obj->data[obj->back] = value;           // 在 数组 back 位置赋值
    if(obj->back == obj->k)
    {//判断 back 位置 是否在数组最后一个空间
        obj->back = 0;      //若 back 在数组最后一个空间，back位置赋值之后，back回到0位置
    }
    else
    {
        obj->back++;    //若 back 不在数组最后一个空间，back 位置++就行
    }

    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj)
{
    assert(obj);

    if(myCircularQueueIsEmpty(obj))
        return false;

    // 思路同上
    if(obj->front == obj->k)
    {
        obj->front = 0;
    }
    else
    {
        obj->front++;
    }

    return true;
}

int myCircularQueueFront(MyCircularQueue* obj)
{
    assert(obj);

    if(myCircularQueueIsEmpty(obj))
        return -1;
    
    return obj->data[obj->front];       //队列不为空直接返回 front位置数据
}

int myCircularQueueRear(MyCircularQueue* obj)
{
    assert(obj);

    if(myCircularQueueIsEmpty(obj))
        return -1;

    // 队列不为空，如果 back 位置在数组首空间(0)，则队列尾元素就是 k 位置的值
    if(obj->back == 0)
    {
        return obj->data[obj->k];
    }
    else
    {// 如果 back 不在数组的首空间，则 队尾元素就是 back - 1 位置的值
        return obj->data[obj->back - 1];
    }
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj)
{
    assert(obj);

    return obj->front == obj->back;
}

bool myCircularQueueIsFull(MyCircularQueue* obj)
{
    assert(obj);

    if(obj->back == obj->k && obj->front == 0)
    {
        return true;
    }
    else
    {
        return obj->back+1 == obj->front;
    }
}

void myCircularQueueFree(MyCircularQueue* obj)
{
    assert(obj);

    free(obj->data);
    free(obj);
}
*/

/*链表实现 思路*/
/*
利用有哨兵位的头节点的单链表 模拟循环队列
队头指针 Front 位置恒为哨兵位的头节点，队尾指针 Back 位置恒为链表最后节点
设置 Len 记录链表长度(循环队列实际元素个数)
设置 LenMax 作为 循环队列长度 k
入队 则新建节点尾插，如果入队前 Len === 0, front->next = newNode,   back = newNode
                   如果入队前 Len !== 0, back->next = newNode,  back = newNode
                   Len++;
出队 则新建标志节点cur = front->next; front->next = cur->next; free(cur);
                 Len--;
判断队空和队满 只需要 判断 Len 和 Len是否等于LenMax 即可
*/
typedef struct SListNode
{
    int data;
    struct SListNode* next;
}SListNode, QueuePointer;

typedef struct
{
    int LenMax;
    int Len;
    QueuePointer* front;
    QueuePointer* back;
} MyCircularQueue;

bool myCircularQueueIsFull(MyCircularQueue* obj);
bool myCircularQueueIsEmpty(MyCircularQueue* obj);

MyCircularQueue* myCircularQueueCreate(int k)
{
    MyCircularQueue* obj = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    assert(obj);
    
    SListNode* newNode = (SListNode*)malloc(sizeof(SListNode));
    assert(newNode);

    obj->front = obj->back = newNode;
    obj->front->next = NULL;
    obj->Len = 0;
    obj->LenMax = k;

    return obj;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value)
{   // 入队操作，如果成功返回 true，不成功返回 false
    assert(obj);
    if(myCircularQueueIsFull(obj))
        return false;

    SListNode* newNode = (SListNode*)malloc(sizeof(SListNode));
    assert(newNode);
    newNode->data = value;
    newNode->next = NULL;
    obj->back->next = newNode;
    obj->back = newNode;
    if(++obj->Len == 1)
    {
        obj->front->next = newNode;
    }

    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj)
{
    assert(obj);
    if(myCircularQueueIsEmpty(obj))
        return false;

    SListNode* cur = obj->front->next;
    if(obj->Len == 1)
    {
        obj->front->next = NULL;
        obj->back = obj->front;
        free(cur);
        --obj->Len;
    }
    else
    {
        obj->front->next = cur->next;
        free(cur);
        --obj->Len;
    }

    return true;
}

int myCircularQueueFront(MyCircularQueue* obj)
{
    assert(obj);
    if(myCircularQueueIsEmpty(obj))
        return -1;

    return obj->front->next->data;
}

int myCircularQueueRear(MyCircularQueue* obj)
{
    assert(obj);
    if(myCircularQueueIsEmpty(obj))
        return -1;
    
    return obj->back->data;
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj)
{
    assert(obj);

    if(obj->Len == 0)
        return true;

    return false;
}

bool myCircularQueueIsFull(MyCircularQueue* obj)
{
    assert(obj);

    if(obj->Len == obj->LenMax)
        return true;
    
    return false;
}

void myCircularQueueFree(MyCircularQueue* obj)
{
    assert(obj);

    while(obj->Len--)
    {
        myCircularQueueDeQueue(obj);
    }

    free(obj);
}

/**
 * Your MyCircularQueue struct will be instantiated and called as such:
 * MyCircularQueue* obj = myCircularQueueCreate(k);
 * bool param_1 = myCircularQueueEnQueue(obj, value);
 
 * bool param_2 = myCircularQueueDeQueue(obj);
 
 * int param_3 = myCircularQueueFront(obj);
 
 * int param_4 = myCircularQueueRear(obj);
 
 * bool param_5 = myCircularQueueIsEmpty(obj);
 
 * bool param_6 = myCircularQueueIsFull(obj);
 
 * myCircularQueueFree(obj);
*/