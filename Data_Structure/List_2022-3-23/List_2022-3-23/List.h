#pragma once

#include <stdio.h>
#include <assert.h>
#include <errno.h>

typedef int LTDataType;

typedef struct ListNode
{
	LTDataType data;
	struct List *next;
	struct List *prev;
}ListNode;


// ˫���ͷѭ������ڵ�
ListNode* BuyListNode(LTDataType x);

// ˫���ͷѭ�������ʼ��
ListNode* ListInit();
//void ListInit(ListNode** pphead);

// ˫���ͷѭ���������
void ListPrint(ListNode* phead);

// ˫���ͷѭ������β��
void ListPushBack(ListNode* phead, LTDataType x);

// ˫���ͷѭ������βɾ
void ListPopBack(ListNode* phead);

// ˫���ͷѭ������ͷ��
void ListPushFront(ListNode* phead, LTDataType x);

// ˫���ͷѭ������βɾ
void ListPopFront(ListNode* phead);

// ˫���ͷѭ������ڵ����
ListNode* ListFind(ListNode* phead, LTDataType x);

// ��pos֮ǰ����
void ListInsert(ListNode* pos, LTDataType x);
//void ListInsert(int i, LTDataType x);

// ɾ��posλ�õĽڵ�
void ListErase(ListNode* pos);

