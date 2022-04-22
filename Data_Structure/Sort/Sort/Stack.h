#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>	// 判断栈 是否为空

typedef int StDateType;

typedef struct Stack
{
	StDateType *data;
	int top;				// 栈顶位置
	int capacity;			// 栈的容量
}Stack;

// 栈的初始化
void StackInit(Stack* pSt);
// 栈的销毁
void StackDestroy(Stack* pSt);
// 压栈
void StackPush(Stack* pSt, StDateType x);
// 出栈
void StackPop(Stack* pSt);
// 判空
bool StackEmpty(Stack* pSt);
// 栈顶数据
StDateType StackTop(Stack* pSt);