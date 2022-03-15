#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int SLTDateType;

typedef struct SListNode
{
	SLTDateType date;
	struct SListNode *next;
}SListNode; 

// 链表的打印
void SListPrint(SListNode *phead);

// 链表尾插
void SListPushBack(SListNode **pphead, SLTDateType x);

void SListPopFront(SListNode **pphead);

void SListPushFront(SListNode **pphead, SLTDateType x);