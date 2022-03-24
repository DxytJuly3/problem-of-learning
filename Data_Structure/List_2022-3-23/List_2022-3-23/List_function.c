#define _CRT_SECURE_NO_WARNINGS 1

#include "List.h"
// 双向带头循环链表节点
ListNode* BuyListNode(LTDataType x)
{
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	if (newNode != NULL)
	{
		newNode->data = x;
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	else
	{
		printf("BuyListNode failed!\n");
	}

	return newNode;
}
// 双向带头循环链表初始化
ListNode* ListInit()
{
	// 双向带头循环链表 初始化需要将头结点的 next 和 prev 都指向自己 以保证是循环的
	ListNode* phead = BuyListNode(0);
	phead->next = phead;
	phead->prev = phead;

	return phead;
}
//void ListInit(ListNode** pphead)
//{
//	assert(pphead);
//
//	*pphead = BuyListNode(0);
//	(*pphead)->next = *pphead;
//	(*pphead)->prev = *pphead;
//}

// 双向带头循环链表输出
void ListPrint(ListNode* phead)
{
	assert(phead);

	ListNode* cur = phead->next;	
	while (cur != phead)	
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

// 双向带头循环链表尾插
void ListPushBack(ListNode* phead, LTDataType x)
{
	assert(phead);

	ListNode* newNode = BuyListNode(x);
	ListNode* Prev = phead->prev;

	newNode->prev = Prev;
	newNode->next = phead;
	Prev->next = newNode;
	phead->prev = newNode;
}