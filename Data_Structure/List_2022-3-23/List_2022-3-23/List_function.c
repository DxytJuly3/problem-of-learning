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

	/*ListNode* newNode = BuyListNode(x);
	ListNode* Prev = phead->prev;

	newNode->prev = Prev;
	newNode->next = phead;
	Prev->next = newNode;
	phead->prev = newNode;*/

	ListInsert(phead, x);
}

// 双向带头循环链表尾删
void ListPopBack(ListNode* phead)
{
	assert(phead);
	assert(phead->next != phead);	//断言链表中一定有数据节点

	/*ListNode* Prev = phead->prev;	//头结点的前一节点 （尾节点）
	ListNode* Prevv = Prev->prev;	//尾节点的前一节点

	Prevv->next = phead;
	phead->prev = Prevv;
	
	free(Prev);
	Prev = NULL;*/

	ListErase(phead->prev);
}

// 双向带头循环链表头插
void ListPushFront(ListNode* phead, LTDataType x)
{
	assert(phead);

	/*ListNode* newNode = BuyListNode(x);
	ListNode* next = phead->next;

	newNode->next = next;
	newNode->prev = phead;
	phead->next = newNode;
	next->prev = newNode;*/

	ListInsert(phead->next, x);
}

// 双向带头循环链表头删
void ListPopFront(ListNode* phead)
{
	assert(phead);
	assert(phead->next != phead);	//断言链表中一定有数据节点

	/*ListNode* tail = phead->next;
	ListNode* tailNext = tail->next;

	phead->next = tailNext;
	tailNext->prev = phead;

	free(tail);
	tail = NULL;*/

	ListErase(phead->next);
}

// 双向带头循环链表节点查找
ListNode* ListFind(ListNode* phead, LTDataType x)
{
	assert(phead);

	ListNode* cur = phead->next;
	while (cur != phead)
	{
		if (cur->data == x)
		{
			return cur;
		}

		cur = cur->next;
	}

	return NULL;
}

// 在pos之前插入
void ListInsert(ListNode* pos, LTDataType x)
{
	assert(pos);

	ListNode* newNode = BuyListNode(x);
	ListNode* Prev = pos->prev;

	newNode->prev = Prev;
	newNode->next = pos;
	pos->prev = newNode;
	Prev->next = newNode;
}

// 删除pos位置的节点
void ListErase(ListNode* pos)
{
	assert(pos);
	// 这里其实也需要断言 pos 不等于 链表的哨兵位节点

	ListNode* posNext = pos->next;
	ListNode* posPrev = pos->prev;

	posNext->prev = posPrev;
	posPrev->next = posNext;

	free(pos);
	pos = NULL;
}

// 销毁单链表
void ListDestroy(ListNode** pphead)
{
	assert(pphead);
	assert(*pphead);

	ListNode* cur = (*pphead)->next;
	while (cur != *pphead)
	{
		ListNode* next = cur->next;
		free(cur);
		// ListErase(cur);
		cur = next;
	}

	free(*pphead);
	*pphead = NULL;
}