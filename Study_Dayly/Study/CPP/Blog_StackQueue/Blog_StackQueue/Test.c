#define _CRT_SECURE_NO_WARNINGS 1

#include "Stack.h"

int main()
{
	Stack st;
	StackInit(&st);
	printf("ջ��Ԫ�ظ���Ϊ :: %d\n", StackSize(&st));
	StackPush(&st, 1);
	printf("ջ��Ԫ�ظ���Ϊ :: %d\n", StackSize(&st));
	StackPush(&st, 2);
	printf("ջ��Ԫ�ظ���Ϊ :: %d\n", StackSize(&st));
	StackPush(&st, 3);
	printf("ջ��Ԫ�ظ���Ϊ :: %d\n", StackSize(&st));
	StackPush(&st, 4);
	printf("ջ��Ԫ�ظ���Ϊ :: %d\n", StackSize(&st));
	StackDestory(&st);

	return 0;
}