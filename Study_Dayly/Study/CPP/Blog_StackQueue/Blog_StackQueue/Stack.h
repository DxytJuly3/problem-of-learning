#pragma once
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int StackDataType;

typedef struct Stack
{
	StackDataType *data;
	int Top;
	int Capacity;
}Stack;
// 初始化
void StackInit(Stack *pst);
// 压栈
void StackPush(Stack *pst, StackDataType x);
// 出栈
void StackPop(Stack *pst);
// 取栈顶元素
StackDataType StackTop(const Stack *pst);
// 判空
bool StackEmpty(const Stack *pst);
// 栈元素个数
int StackSize(const Stack *pst);
// 栈销毁
void StackDestory(Stack *pst);