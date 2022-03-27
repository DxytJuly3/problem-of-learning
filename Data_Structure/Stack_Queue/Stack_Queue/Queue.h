#pragma once

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>	// 判断队列 是否为空

typedef int QDatetype;

typedef struct QueueNode
{
	QDatetype date;
	struct QueueNode* next;
}QNode;

typedef struct Queue
{
	QNode* head;			// 队列头
	QNode* tail;			// 队列尾
}Queue;

// 队列初始化
void QueueInit(Queue* pq);
// 队列销毁
void QueueDestroy(Queue *pq);
// 入队列
void QueuePush(Queue *pq, QDatetype x);
// 出队列
void QueuePop(Queue *pq);
// 队列判空
bool QueueEmpty(Queue *pq);
// 队列长度
size_t QueueSize(Queue *pq);
// 队列头 数据
QDatetype QueueFront(Queue *pq);
// 队列尾 数据
QDatetype QueueBack(Queue *pq);
