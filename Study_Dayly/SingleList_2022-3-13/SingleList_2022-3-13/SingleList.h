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

// ����Ĵ�ӡ
void SListPrint(SListNode *phead);

// ����β��
void SListPushBack(SListNode **pphead, SLTDateType x);

void SListPopFront(SListNode **pphead);

void SListPushFront(SListNode **pphead, SLTDateType x);