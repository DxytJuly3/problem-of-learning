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
	assert(pphead);

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

// 单链表头插
void SListPushFront(SListNode **pphead, SLTDateType x)
{
	assert(pphead);

	SListNode* newnode = BuySLTNode(x);
	newnode->next = *pphead;			//pphead 二级指针，是 &phead
	*pphead = newnode;
}

// 单链表尾删
void SListPopBack(SListNode **pphead)
{
	assert(pphead);

	// 1.没有节点
	// 2.只有一个节点
	// 3.多个节点
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
		SListNode *prev = NULL;
		SListNode *cur = *pphead;
		while (cur->next != NULL)
		{
			prev = cur;
			cur = cur->next;
		}

		free(cur);
		cur = NULL;
		prev->next = NULL;
	}
}
// 单链表头删
void SListPopFront(SListNode **pphead)
{
	assert(pphead);

	if (*pphead == NULL)
	{
		return;
	}
	else
	{
		SListNode* tail = (*pphead)->next;
		free(*pphead);
		*pphead = tail;
	}
}

// 查找 x 所在位置 pos
SListNode* SListFind(SListNode *phead, SLTDateType x)
{
	SListNode *cur = phead;
	while (cur != NULL)
	{
		if (cur->date != x)
			cur = cur->next;
		else
			return cur;
		/*if (cur->date == x)
		return cur;

		cur = cur->next;*/
	}

	return NULL;
}

// 在pos位置之前插入
void SListInsert(SListNode **pphead, SListNode *pos, SLTDateType x)
{
	assert(pphead);
	assert(pos);

	if (pos == *pphead)
	{ // pos是链表中第一个节点  直接头插
		SListPushFront(pphead, x);
	}
	else
	{
		SListNode *cur = *pphead;
		while (cur->next != pos)
		{
			cur = cur->next;
		}

		SListNode *newNode = BuySLTNode(x);
		newNode->next = pos;
		cur->next = newNode;
	}
}

// 在pos位置之后插入
void SListInsertAfter(SListNode *pos, SLTDateType x)
{// 因为 直接将新节点链接到 pos 节点之后，所以不需要原单链表的首节点
	assert(pos);

	SListNode *newNode = BuySLTNode(x);
	newNode->next = pos->next;
	pos->next = newNode;
}

// 删除pos位置节点
void SListErase(SListNode **pphead, SListNode *pos)
{
	assert(pphead);
	assert(pos);

	if (pos == *pphead)
	{
		SListPopFront(pphead);
	}
	else
	{
		SListNode *cur = *pphead;
		while (cur->next != pos)
		{
			cur = cur->next;
		}
		cur->next = pos->next;
		free(pos);
		pos = NULL;
	}
}

// 删除pos位置之后节点
void SListEraseAfter(SListNode *pos)
{
	assert(pos);

	SListNode* next = pos->next;
	if (next)
	{
		pos->next = next->next;
		free(next);
		next = NULL;
	}
}

// 销毁单链表
void SListDestroy(SListNode **pphead)
{
	assert(pphead);
	// 要点就是 在free当前节点的时候， 需要将当前节点的 next 节点 存起来，以保证可以找到
	SListNode *cur = *pphead;
	while (cur != NULL)
	{
		SListNode *next = cur->next;
		free(cur);
		cur = next;
	}

	*pphead = NULL;
}

