#define _CRT_SECURE_NO_WARNINGS 1
#include "Stack.h"

// 初始化
void StackInit(Stack *pst)
{
	assert(pst);
	pst->data = NULL;
	pst->Top = pst->Capacity = 0;
}
// 压栈
void StackPush(Stack *pst, StackDataType x)
{
	assert(pst);

	if (pst->Top == pst->Capacity)		// 数组已满
	{
		int newCapacity = pst->Capacity == 0 ? 4 : pst->Capacity * 2;
		StackDataType *tmp = (StackDataType*)realloc(pst->data, sizeof(StackDataType)* newCapacity);
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}

		pst->data = tmp;
		pst->Capacity = newCapacity;
	}

	pst->data[pst->Top++] = x;
}

// 出栈
void StackPop(Stack *pst)
{
	assert(pst);
	assert(pst->Top > 0);		//保证栈不为空
	/*	Top 初值为 -1
	assert(pst->Top > -1);
	*/

	--pst->Top;
}

// 取栈顶元素
StackDataType StackTop(const Stack *pst)
{
	assert(pst);
	assert(pst->Top > 0);	

	return pst->data[pst->Top - 1];
	/*	Top 初值为 -1
	return pst->data[pst->Top];
	*/
}

// 判空
bool StackEmpty(const Stack *pst)
{
	assert(pst);

	return pst->Top == 0;
	/*	Top 初值为 -1
	return pst->Top == -1;
	*/
}

// 栈元素个数
int StackSize(const Stack *pst)
{
	assert(pst);

	return pst->Top;
	/*	Top 初值为 -1
	return pst->Top + 1;
	*/
}

// 栈销毁
void StackDestory(Stack *pst)
{
	assert(pst);

	free(pst->data);
	pst->data = NULL;
	pst->Capacity = pst->Top = 0;
}