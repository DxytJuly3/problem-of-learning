#define _CRT_SECURE_NO_WARNINGS 1

#include "SingleList.h"

int main()
{
	SListNode *phead = NULL;
	SListPushBack(&phead, 1);
	SListPushBack(&phead, 2);
	SListPushBack(&phead, 3);
	SListPushBack(&phead, 4);
	SListPrint(phead);
	SListPopFront(&phead);
	SListPrint(phead);
	SListPopFront(&phead);
	SListPrint(phead);
	SListPopFront(&phead);
	SListPrint(phead);
	SListPopFront(&phead);
	SListPrint(phead);

	return 0;
}