#define _CRT_SECURE_NO_WARNINGS 1

#include "List.h"
// ˫���ͷѭ������ڵ�
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
// ˫���ͷѭ�������ʼ��
ListNode* ListInit()
{
	// ˫���ͷѭ������ ��ʼ����Ҫ��ͷ���� next �� prev ��ָ���Լ� �Ա�֤��ѭ����
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

// ˫���ͷѭ���������
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

// ˫���ͷѭ������β��
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