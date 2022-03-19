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

// 单链表头插
void SListPushFront(SListNode **pphead, SLTDateType x);

// 单链表头删
void SListPopFront(SListNode **pphead);

// 单链表尾删
void SListPopBack(SListNode **pphead);

// 查找 x 所在位置 pos
SListNode* SListFind(SListNode *phead, SLTDateType x);

// 在pos位置之前插入
void SListInsert(SListNode **pphead, SListNode *pos, SLTDateType x);

// 在pos位置之后插入
void SListInsertAfter(SListNode *pos, SLTDateType x);

// 删除pos位置节点
void SListErase(SListNode **pphead, SListNode *pos);

// 删除pos位置之后节点
void SListEraseAfter(SListNode *pos);

// 销毁单链表
void SListDestroy(SListNode **pphead);