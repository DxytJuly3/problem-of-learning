/*
请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：

实现 MyQueue 类：

    void push(int x) 将元素 x 推到队列的末尾
    int pop() 从队列的开头移除并返回元素
    int peek() 返回队列开头的元素
    boolean empty() 如果队列为空，返回 true ；否则，返回 false

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/implement-queue-using-stacks
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

typedef int StDateType;

typedef struct Stack
{
	StDateType *data;
	int top;				// 栈顶位置
	int capacity;			// 栈的容量
}Stack;

// 栈的初始化
void StackInit(Stack* pSt)
{
	assert(pSt);

	pSt->data = NULL;
	pSt->top = 0;			 // 栈顶初始位置定义 (top = -1, 先++后赋值; top = 0, 先赋值后++)
	pSt->capacity = 0;
}
// 栈的销毁
void StackDestroy(Stack* pSt)
{
	assert(pSt);

	free(pSt->data);
	pSt->data = NULL;
	pSt->top = pSt->capacity = 0;
}
// 压栈
void StackPush(Stack* pSt, StDateType x)
{
	assert(pSt);

	if (pSt->top == pSt->capacity)
	{
		int newCapacity = pSt->capacity == 0 ? 4 : pSt->capacity * 2;
		pSt->data = (StDateType*)realloc(pSt->data, newCapacity * sizeof(StDateType));
		assert(pSt->data);

		pSt->capacity = newCapacity;
	}

	pSt->data[pSt->top++] = x;
}
// 出栈
void StackPop(Stack* pSt)
{
	assert(pSt);
	assert(pSt->top > 0);

	--pSt->top;
}
// 判空
bool StackEmpty(Stack* pSt)
{
	assert(pSt);

	return pSt->top == 0;			// top 等于 0 栈为空，返回 true; 不等于 0 ，返回 false
}
// 栈顶数据
StDateType StackTop(Stack* pSt)
{
	assert(pSt);

	return pSt->data[pSt->top - 1];
}

/* 思路1*/
// 用两个队列来模拟 队列
// 固定一个栈为模拟队列(st1)  一直存放数据   固定另一个栈为辅助栈(st2)，每次操作结束后，数据返回另一个栈
// 模拟入队，即 在 st1 压栈
// 模拟出栈，即 使 st1 除栈底外 的数据，逐一出栈，且存放至 st2 中（栈底数据不存放）
// 然后使 st1 最后一个数据出栈，使 st1 置空，再将st2 中的所有数据，逐一出栈，且存放至 st1

// 即 st1 就是模拟队列存放数据， 另一个栈 为辅助栈，用来辅助实现队列效果

typedef struct
{
    // 固定 st1 为存放数据的栈，模拟队列存放数据
    // st2 为辅助栈，用来辅助实现队列效果
    // 所以需要保证在每次操作结束时， st2 为空，st1 中的数据 为操作后的结果
    Stack st1;
    Stack st2;
} MyQueue;


MyQueue* myQueueCreate()
{
    // 特别注意 需要返回地址 所以需要 malloc
    MyQueue* Que = (MyQueue*)malloc(sizeof(MyQueue));
    assert(Que);
    
    StackInit(&Que->st1);
    StackInit(&Que->st2);

    return Que;
}

void myQueuePush(MyQueue* obj, int x)
{
    assert(obj);

    // 入队 直接在 st1 中压栈
    StackPush(&obj->st1, x);
}

int myQueuePop(MyQueue* obj)
{
    assert(obj);

    // 使 st1 中除了栈底的数据，注意出栈，并存放至 st2
    while((&obj->st1)->top > 1)
    {
        StackPush(&obj->st2, StackTop(&obj->st1));
        StackPop(&obj->st1);
    }

    // 存储 st1 栈底数据(保证返回正确)后，出栈 至 st1 为空
    int top = StackTop(&obj->st1);
    StackPop(&obj->st1);

    // 再将 st2 中数据，逐一出栈，且存放入 st1
    // 保证 st1 数据正确
    while((&obj->st2)->top > 0)
    {
        StackPush(&obj->st1, StackTop(&obj->st2));
        StackPop(&obj->st2);
    }

    return top;
}

int myQueuePeek(MyQueue* obj)
{
    assert(obj);

    while((&obj->st1)->top > 1)
    {
        StackPush(&obj->st2, StackTop(&obj->st1));
        StackPop(&obj->st1);
    }

    int top = StackTop(&obj->st1);

    while((&obj->st2)->top > 0)
    {
        StackPush(&obj->st1, StackTop(&obj->st2));
        StackPop(&obj->st2);
    }

    return top;
}

bool myQueueEmpty(MyQueue* obj)
{
    assert(obj);

    return StackEmpty(&obj->st1);
}

void myQueueFree(MyQueue* obj)
{
    assert(obj);

    StackDestroy(&obj->st1);
    StackDestroy(&obj->st2);

    free(obj);
}


/* 思路2 */
// 两个栈
// 固定一个为 pushSt 模拟入队列操作，即对其压栈
// 固定一个为 popSt 模拟出队列操作，即对齐其出栈

// 求模拟队列头数据：
// 若 popSt 有数据，则 popSt 栈顶即为 模拟队列头数据
// 若 popSt 无数据，则 pushSt 数据全出栈且存入 popSt，则popSt 栈顶还为 模拟队列头数据

/*
typedef struct
{
    Stack pushSt;
    Stack popSt;
} MyQueue;


MyQueue* myQueueCreate()
{
    MyQueue* Que = (MyQueue*)malloc(sizeof(MyQueue));
    assert(Que);
    
    StackInit(&Que->pushSt);
    StackInit(&Que->popSt);

    return Que;
}

void myQueuePush(MyQueue* obj, int x)
{
    assert(obj);

    // 模拟入队 直接在 pushSt 中压栈
    StackPush(&obj->pushSt, x);
}

int myQueuePop(MyQueue* obj)
{
    assert(obj);

    int top = 0;
    if((&obj->popSt)->top == 0)
    {
        while((&obj->pushSt)->top > 1)
        {
            StackPush(&obj->popSt, StackTop(&obj->pushSt));
            StackPop(&obj->pushSt);
        }

        top = StackTop(&obj->pushSt);
        StackPop(&obj->pushSt);
    }
    else
    {
        top = StackTop(&obj->popSt);
        StackPop(&obj->popSt);
    }

    return top;
}

int myQueuePeek(MyQueue* obj)
{
    assert(obj);

    int top = 0;
    if((&obj->popSt)->top != 0)
    {
        return StackTop(&obj->popSt);
    }
    else
    {
        while((&obj->pushSt)->top > 0)
        {
            StackPush(&obj->popSt, StackTop(&obj->pushSt));
            StackPop(&obj->pushSt);
        }

        return StackTop(&obj->popSt);
    }
}

bool myQueueEmpty(MyQueue* obj)
{
    assert(obj);

    return StackEmpty(&obj->popSt) && StackEmpty(&obj->pushSt);
}

void myQueueFree(MyQueue* obj)
{
    assert(obj);

    StackDestroy(&obj->pushSt);
    StackDestroy(&obj->popSt);

    free(obj);
}
*/
/**
 * Your MyQueue struct will be instantiated and called as such:
 * MyQueue* obj = myQueueCreate();
 * myQueuePush(obj, x);
 
 * int param_2 = myQueuePop(obj);
 
 * int param_3 = myQueuePeek(obj);
 
 * bool param_4 = myQueueEmpty(obj);
 
 * myQueueFree(obj);
*/