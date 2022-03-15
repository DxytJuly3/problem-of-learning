#define _CRT_SECURE_NO_WARNINGS 1
#include "SingleList.h"

// 链表建立新数据节点
SListNode* BuySLTNode(SLTDateType x)
{
	SListNode* newnode = (SListNode*)malloc(sizeof(SListNode));
	if (newnode == NULL)
	{
		printf("malloc fail\n");
		exit(-1);
	}
	else
	{
		newnode->date = x;
		newnode->next = NULL;
	}

	return newnode;
}

// 链表的打印
void SListPrint(SListNode* phead)
{
	SListNode* cur = phead;
	while (cur != NULL)
	{
		printf("%d->", cur->date);
		cur = cur->next;
	}
	printf("NULL\n");
}

// 链表尾插
void SListPushBack(SListNode **pphead, SLTDateType x)
{
	SListNode* newnode = BuySLTNode(x);
	if (*pphead == NULL)
	{// 链表头节点为空 （即链表为空）
		*pphead = newnode;
	}
	else
	{// 链表不为空
		//找尾
		SListNode* tail = *pphead;
		while (tail->next != NULL)
		{//循环 找到 tail->next 为 NULL
			tail = tail->next;
		}
		// 找到 tail->next 为 NULL, 即找到 原单链表的尾，再把尾指向新数据节点
		tail->next = newnode;
	}
}

void SListPushFront(SListNode **pphead, SLTDateType x)
{
	SListNode* newnode = BuySLTNode(x);
	newnode->next = *pphead;			//pphead 二级指针，是 &phead
	*pphead = newnode;
}

void SListPopFront(SListNode **pphead)
{
	assert(pphead);

	if (*pphead == NULL)
	{
		return;
	}
	else if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		SListNode* tail = (*pphead)->next;
		free(*pphead);
		*pphead = tail;
	}
}