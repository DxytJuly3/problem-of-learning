#define _CRT_SECURE_NO_WARNINGS 1

#include "Stack.h"

int main()
{
	Stack st;
	StackInit(&st);
	printf("栈中元素个数为 :: %d\n", StackSize(&st));
	StackPush(&st, 1);
	printf("栈中元素个数为 :: %d\n", StackSize(&st));
	StackPush(&st, 2);
	printf("栈中元素个数为 :: %d\n", StackSize(&st));
	StackPush(&st, 3);
	printf("栈中元素个数为 :: %d\n", StackSize(&st));
	StackPush(&st, 4);
	printf("栈中元素个数为 :: %d\n", StackSize(&st));
	StackDestory(&st);

	return 0;
}