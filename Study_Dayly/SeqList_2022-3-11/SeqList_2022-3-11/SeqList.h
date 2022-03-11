#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int SLDateType;		// 重命名 数据类型

typedef struct SeqList
{
	SLDateType *s;
	int size;				// 顺序表中存入的数据个数
	int capacity;			// 本顺序表的容量
}SL, SeqList;

// 顺序表初始化
void SeqListInit(SeqList *psl);
// 顺序表打印
void SeqListPrint(SeqList *psl);
// 顺序表容量检查
void SeqListCheckCapacity(SeqList* psl);
// 顺序表尾插
void SeqListPushBack(SeqList *psl, SLDateType x);
// 顺序表尾删
void SeqListPopBack(SeqList *psl);
// 顺序表前插
void SeqListPushFront(SeqList *psl, SLDateType x);
// 顺序表前删
void SeqListPopFront(SeqList *psl);
// 顺序表插入
void SeqListInsert(SeqList *psl, size_t pos, SLDateType x);