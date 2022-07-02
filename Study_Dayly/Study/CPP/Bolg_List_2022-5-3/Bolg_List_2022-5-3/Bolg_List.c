#define _CRT_SECURE_NO_WARNINGS 1
#include "Blog_List.h"

ListNode* BuyListNode(ListDataType x)
{
	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	if (newNode == NULL)
	{
		printf("BuyListNode fail!\n");
		exit(-1);
	}

	newNode->val = x;
	newNode->prev = NULL;
	newNode->next = NULL;

	return newNode;
}

//void ListInit(ListNode **pphead)
//{
//	assert(pphead);
//
//	*pphead = BuyListNode(0);
//	(*pphead)->next = *pphead;
//	(*pphead)->prev = *pphead;
//}
ListNode* ListInit()
{
	ListNode *phead = BuyListNode(0);
	phead->next = phead;
	phead->prev = phead;

	return phead;
}

void ListPushBack(ListNode *phead, ListDataType x)
{
	assert(phead);

	ListNode *newNode = BuyListNode(x);
	ListNode *tail = phead->prev;

	newNode->prev = tail;
	tail->next = newNode;

	newNode->next = phead;
	phead->prev = newNode;
}

void ListPopBack(ListNode *phead)
{
	assert(phead);
	if (phead->next == phead)
	{
		return;					// 防止只有头节点
	}

	ListNode *tail = phead->prev;
	ListNode *tailPrev = tail->prev;		//记录尾节点的prev 防止重找

	tailPrev->next = phead;
	phead->prev = tailPrev;

	free(tail);
	tail = NULL;
}

void ListPrint(ListNode *phead)
{
	assert(phead);

	ListNode *tail = phead->next;
	while (tail != phead)
	{
		printf("<-%d->", tail->val);
		tail = tail->next;
	}
	printf("\n");
}

void ListPushFront(ListNode *phead, ListDataType x)
{
	assert(phead);

	ListNode *newNode = BuyListNode(x);
	ListNode *Next = phead->next;

	Next->prev = newNode;
	newNode->next = Next;

	newNode->prev = phead;
	phead->next = newNode;
}

void ListPopFront(ListNode *phead)
{
	assert(phead);
	assert(phead->next != phead);

	ListNode* Next = phead->next->next;
	free(phead->next);

	phead->next = Next;
	Next->prev = phead;
}

ListNode* ListFind(ListNode *phead, ListDataType x)
{
	assert(phead);

	ListNode* cur = phead->next;
	while (cur != phead)
	{
		if (cur->val == x)
		{
			return cur;
		}

		cur = cur->next;
	}

	return NULL;
}

void ListInsert(ListNode *pos, ListDataType x)
{
	assert(pos);

	ListNode *newNode = BuyListNode(x);
	ListNode *posPrev = pos->prev;

	posPrev->next = newNode;
	newNode->prev = posPrev;

	newNode->next = pos;
	pos->prev = newNode;
}

void ListErase(ListNode *pos)
{
	assert(pos);

	ListNode* posPrev = pos->prev;
	ListNode* posNext = pos->next;

	free(pos);
	pos = NULL;

	posPrev->next = posNext;
	posNext->prev = posPrev;
}

void ListDestroy(ListNode *phead)
{
	assert(phead);

	ListNode *cur = phead->next;
	while (cur != phead)
	{
		ListNode *Next = cur->next;
		free(cur);
		cur = Next;
	}
	free(phead);
}