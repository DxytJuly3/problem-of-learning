/*
请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。

实现 MyStack 类：

    void push(int x) 将元素 x 压入栈顶。
    int pop() 移除并返回栈顶元素。
    int top() 返回栈顶元素。
    boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-stack-using-queues
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

typedef int QDatetype;

typedef struct QueueNode
{
	QDatetype date;
	struct QueueNode* next;
}QNode;

typedef struct Queue
{
	QNode* head;			// 队列头
	QNode* tail;			// 队列尾
}Queue;

// 队列初始化
void QueueInit(Queue* pq)
{
	assert(pq);

	pq->head = pq->tail = NULL;		// 队列头、 队列尾 同时赋 NULL
}
// 队列销毁
void QueueDestroy(Queue *pq)
{
	assert(pq);

	QNode* cur = pq->head;
	while (cur)						// pq->tail->next 就为 NULL
	{
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}

	pq->head = pq->tail = NULL;		// 队列数据销毁后，头尾指针 置空
}
// 入队列
void QueuePush(Queue *pq, QDatetype x)
{
	assert(pq);

	QNode* tmp = (QNode*)malloc(sizeof(QNode));
	if (tmp == NULL)
	{
		printf("malloc failed\n");
		return ;
	}
	QNode* newNode = tmp;
	newNode->date = x;
	newNode->next = NULL;

	if (pq->head == NULL)
	{
		pq->head = pq->tail = newNode;
	}
	else
	{
		pq->tail->next = newNode;
		pq->tail = newNode;
	}
}
// 出队列
void QueuePop(Queue *pq)
{
	assert(pq);
	assert(pq->head != NULL && pq->tail != NULL);

	if (pq->head->next == NULL)
	{
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else
	{
		QNode* HeadNext = pq->head->next;
		free(pq->head);
		pq->head = HeadNext;
	}
}
// 队列判空
bool QueueEmpty(Queue *pq)
{
	assert(pq);

	return pq->head == NULL;
}
// 队列长度
size_t QueueSize(Queue *pq)
{
	assert(pq);

	QNode* cur = pq->head;
	size_t size = 0;
	while (cur)
	{
		++size;
		cur = cur->next;
	}

	return size;
}
// 队列头 数据
QDatetype QueueFront(Queue *pq)
{
	assert(pq);
	assert(pq->head);

	return pq->head->date;
}
// 队列尾 数据
QDatetype QueueBack(Queue *pq)
{
	assert(pq);
	assert(pq->tail);

	return pq->tail->date;
}

// 用两个队列来模拟 栈
// 保证一个队列为空 另一个队列存放数据
// 模拟压栈，即 在非空队列 进行入队操作
// 模拟出栈，即 使非空队列中的数据 (除最后一个(队尾，即模拟栈的栈顶)外) 按顺序入队至另一个空队列，并对原非空队列所有数据 出队操作
//  即 非空队列就是 返回的栈， 空队列是辅助队列，用来调整 模拟栈
// 非空队列和空队列是相对的
typedef struct
{
    Queue q1;
    Queue q2;
} MyStack;


MyStack* myStackCreate()
{
    // 特别注意 需要返回地址 所以需要 malloc
    MyStack* Ms = (MyStack*)malloc(sizeof(MyStack));
    assert(Ms);

    QueueInit(&Ms->q1);
    QueueInit(&Ms->q2);

    return Ms;
}

void myStackPush(MyStack* obj, int x)
{
    assert(obj);

    // 对非空队列进行入队操作 模拟压栈
    if(!QueueEmpty(&obj->q1))
    {
        QueuePush(&obj->q1, x);
    }
    else
    {
        QueuePush(&obj->q2, x);
    }
}

int myStackPop(MyStack* obj)
{
    assert(obj);

    // 随便让 两个变量 分别 指向两个队列，分别 代表空队列 非空队列
    // 然后判断 空队列是否为空，不是则交换
    Queue* EmptyQue = &obj->q1;
    Queue* UnEmptyQue = &obj->q2;
    if(!QueueEmpty(EmptyQue))
    {
        EmptyQue = &obj->q2;
        UnEmptyQue = &obj->q1;
    }

    while(QueueSize(UnEmptyQue) > 1)
    {// 非空队列的大小 > 1进循环
        // 将非空队列的 前 n-1 个数据，入队至另一个队列
        QueuePush(EmptyQue, QueueFront(UnEmptyQue));
        QueuePop(UnEmptyQue);
    }

    // 循环结束，原非空队列还剩最后一个数据，此数据即为需要出栈和返回的数据
    int top = QueueBack(UnEmptyQue);
    QueuePop(UnEmptyQue);

    return top;
}

int myStackTop(MyStack* obj)
{
    assert(obj);

    Queue* EmptyQue = &obj->q1;
    Queue* UnEmptyQue = &obj->q2;
    if(!QueueEmpty(EmptyQue))
    {
        EmptyQue = &obj->q2;
        UnEmptyQue = &obj->q1;
    }

    // 返回非空队列的 队尾数据（即为模拟栈的栈顶）
    return QueueBack(UnEmptyQue);
}

bool myStackEmpty(MyStack* obj)
{
    assert(obj);

    return QueueEmpty(&obj->q1) && QueueEmpty(&obj->q2);
}

void myStackFree(MyStack* obj)
{
    assert(obj);

    QueueDestroy(&obj->q1);
    QueueDestroy(&obj->q2);

    free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/