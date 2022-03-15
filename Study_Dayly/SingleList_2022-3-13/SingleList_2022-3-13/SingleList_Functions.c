#define _CRT_SECURE_NO_WARNINGS 1
#include "SingleList.h"

// �����������ݽڵ�
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

// ����Ĵ�ӡ
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

// ����β��
void SListPushBack(SListNode **pphead, SLTDateType x)
{
	SListNode* newnode = BuySLTNode(x);
	if (*pphead == NULL)
	{// ����ͷ�ڵ�Ϊ�� ��������Ϊ�գ�
		*pphead = newnode;
	}
	else
	{// ����Ϊ��
		//��β
		SListNode* tail = *pphead;
		while (tail->next != NULL)
		{//ѭ�� �ҵ� tail->next Ϊ NULL
			tail = tail->next;
		}
		// �ҵ� tail->next Ϊ NULL, ���ҵ� ԭ�������β���ٰ�βָ�������ݽڵ�
		tail->next = newnode;
	}
}

void SListPushFront(SListNode **pphead, SLTDateType x)
{
	SListNode* newnode = BuySLTNode(x);
	newnode->next = *pphead;			//pphead ����ָ�룬�� &phead
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