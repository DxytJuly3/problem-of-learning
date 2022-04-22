#define _CRT_SECURE_NO_WARNINGS 1

#include "Stack.h"

// 栈的初始化
void StackInit(Stack* pSt)
{
	assert(pSt);

	pSt->data = NULL;
	pSt->top = 0;			// 栈顶初始位置定义 (top = -1, 先++后赋值; top = 0, 先赋值后++)
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
		StDateType* tmp = (StDateType*)realloc(pSt->data, newCapacity * sizeof(StDateType));
		if (tmp == NULL)
		{
			printf("realloc failed\n");
			exit(-1);
		}
		else
			pSt->data = tmp;

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