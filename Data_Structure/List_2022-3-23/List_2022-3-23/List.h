#pragma once

#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>

typedef int LTDataType;

typedef struct ListNode
{
	LTDataType data;
	struct ListNode *next;
	struct ListNode *prev;
}ListNode;


// 双向带头循环链表节点
ListNode* BuyListNode(LTDataType x);

// 双向带头循环链表初始化
ListNode* ListInit();
//void ListInit(ListNode** pphead);

// 双向带头循环链表输出
void ListPrint(ListNode* phead);

// 双向带头循环链表尾插
void ListPushBack(ListNode* phead, LTDataType x);

// 双向带头循环链表尾删
void ListPopBack(ListNode* phead);

// 双向带头循环链表头插
void ListPushFront(ListNode* phead, LTDataType x);

// 双向带头循环链表头删
void ListPopFront(ListNode* phead);

// 双向带头循环链表节点查找
ListNode* ListFind(ListNode* phead, LTDataType x);

// 在pos之前插入
void ListInsert(ListNode* pos, LTDataType x);

// 删除pos位置的节点
void ListErase(ListNode* pos);

// 销毁单链表
void ListDestroy(ListNode** phead);

