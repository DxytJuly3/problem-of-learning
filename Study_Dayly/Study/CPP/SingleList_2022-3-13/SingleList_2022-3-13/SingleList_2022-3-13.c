#define _CRT_SECURE_NO_WARNINGS 1

#include "SingleList.h"

void test1()
{
	SListNode *phead = NULL;
	SListPushFront(&phead, 1);
	SListPushFront(&phead, 2);
	SListPushFront(&phead, 3);
	SListPushFront(&phead, 4);
	SListPushFront(&phead, 5);
	SListPrint(phead);
	SListNode *pos = SListFind(phead, 7);
	printf("%p", pos);
}

void test2()
{
	SListNode *phead = NULL;
	SListPushFront(&phead, 1);
	SListPushFront(&phead, 2);
	SListPushFront(&phead, 3);
	SListPushFront(&phead, 4);
	SListPushFront(&phead, 5);
	SListPrint(phead);
	SListPopBack(&phead);
	SListPopBack(&phead);
	SListPopBack(&phead);
	SListPopBack(&phead);
	SListPrint(phead);
	SListPopBack(&phead);
	SListPrint(phead);
}

void test3()
{
	SListNode *slist = NULL;
	printf("头插尾插测试:>\n");
	SListPushFront(&slist, 1);
	SListPushFront(&slist, 2);
	SListPushFront(&slist, 3);
	SListPushBack(&slist, 4);
	SListPushBack(&slist, 5);
	SListPushBack(&slist, 6);
	SListPrint(slist);
	printf("\n");
	printf("尾删测试:>\n");
	SListPopBack(&slist);
	SListPrint(slist);
	printf("\n");
	printf("头删测试:>\n");
	SListPopFront(&slist);
	SListPrint(slist);
	printf("\n");
	printf("pos位置之前插入测试(pos 为单链表中 1 的位置):>\n");
	SListNode *pos1 = SListFind(slist, 1);
	if (pos1 != NULL)
	{
		SListInsert(&slist, pos1, 10);
	}
	SListPrint(slist);
	printf("\n");

	printf("pos位置之后插入测试(pos 为单链表中 4 的位置):>\n");
	SListNode *pos2 = SListFind(slist, 4);
	if (pos2 != NULL)
	{
		SListInsertAfter(pos2, 10);
	}
	SListPrint(slist);
	printf("\n");

	printf("pos位置删除测试(pos 为单链表中 4 的位置):>\n");
	SListNode *pos3 = SListFind(slist, 4);
	if (pos3 != NULL)
	{
		SListErase(&slist, pos3);
	}
	SListPrint(slist);
	printf("\n");

	printf("pos位置之后删除测试(pos 为单链表中 10 的位置):>\n");
	SListNode *pos4 = SListFind(slist, 10);
	if (pos4 != NULL)
	{
		SListEraseAfter(pos4);
	}
	SListPrint(slist);
	printf("\n");

	printf("单链表销毁测试:>\n");
	SListDestroy(&slist);
	SListPrint(slist);
	printf("\n");
}

int main()
{
	test3();

	return 0;
}