#pragma once 
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int ListDataType;

typedef struct ListNode
{
	ListDataType val;
	struct ListNode* prev;
	struct ListNode* next;
}ListNode;

//void ListInit(ListNode *phead);
ListNode* ListInit();

ListNode* BuyListNode(ListDataType x);

void ListPushBack(ListNode *phead, ListDataType x);

void ListPopBack(ListNode *phead);

void ListPrint(ListNode *phead);

ListNode* ListFind(ListNode *phead, ListDataType x);

void ListInsert(ListNode *pos, ListDataType x);

void ListErase(ListNode *pos);

void ListPushFront(ListNode *phead, ListDataType x);

void ListPopFront(ListNode *phead);

void ListDestroy(ListNode *phead);