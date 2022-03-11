#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int SLDateType;		// ������ ��������

typedef struct SeqList
{
	SLDateType *s;
	int size;				// ˳����д�������ݸ���
	int capacity;			// ��˳��������
}SL, SeqList;

// ˳����ʼ��
void SeqListInit(SeqList *psl);
// ˳����ӡ
void SeqListPrint(SeqList *psl);
// ˳����������
void SeqListCheckCapacity(SeqList* psl);
// ˳���β��
void SeqListPushBack(SeqList *psl, SLDateType x);
// ˳���βɾ
void SeqListPopBack(SeqList *psl);
// ˳���ǰ��
void SeqListPushFront(SeqList *psl, SLDateType x);
// ˳���ǰɾ
void SeqListPopFront(SeqList *psl);
// ˳������
void SeqListInsert(SeqList *psl, size_t pos, SLDateType x);