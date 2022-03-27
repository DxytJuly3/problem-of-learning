#define _CRT_SECURE_NO_WARNINGS 1


// 栈的测试

/* #include "Stack.h"

void StackTest()
{
	Stack st;
	StackInit(&st);
	StackPush(&st, 1);
	StackPush(&st, 2);
	StackPush(&st, 3);
	StackPush(&st, 4);
	
	while (!StackEmpty(&st))		// 栈不为空 进入循环
	{
		printf("%d ", StackTop(&st));		// 输出栈顶元素
		StackPop(&st);						// 出栈一次
	}
	printf("\n");

	StackDestroy(&st);
}

int main()
{
	StackTest();

	return 0;
}
*/

// 队列的测试
#include "Queue.h"

void QueueTest()
{
	Queue que;
	QueueInit(&que);
	QueuePush(&que, 1);
	QueuePush(&que, 2);
	QueuePush(&que, 3);
	QueuePush(&que, 4);

	while (!QueueEmpty(&que))
	{
		printf("%d ", QueueFront(&que));
		QueuePop(&que);
	}
	printf("\n");

}

int main()
{
	QueueTest();

	return 0;
}