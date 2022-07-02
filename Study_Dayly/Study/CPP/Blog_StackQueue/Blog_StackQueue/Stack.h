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
// ��ʼ��
void StackInit(Stack *pst);
// ѹջ
void StackPush(Stack *pst, StackDataType x);
// ��ջ
void StackPop(Stack *pst);
// ȡջ��Ԫ��
StackDataType StackTop(const Stack *pst);
// �п�
bool StackEmpty(const Stack *pst);
// ջԪ�ظ���
int StackSize(const Stack *pst);
// ջ����
void StackDestory(Stack *pst);