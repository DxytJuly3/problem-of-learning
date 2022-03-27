#define _CRT_SECURE_NO_WARNINGS 1

#include "Queue.h"

// 队列初始化
void QueueInit(Queue* pq)
{
	assert(pq);

	pq->head = pq->tail = NULL;		// 队列头、 队列尾 同时赋 NULL
}
// 队列销毁
void QueueDestroy(Queue *pq)
{
	assert(pq);

	QNode* cur = pq->head;
	while (cur)						// pq->tail->next 就为 NULL
	{
		QNode* next = cur->next;
		free(cur);
		cur = next;
	}

	pq->head = pq->tail = NULL;		// 队列数据销毁后，头尾指针 置空
}
// 入队列
void QueuePush(Queue *pq, QDatetype x)
{
	assert(pq);

	QNode* tmp = (QNode*)malloc(sizeof(QNode));
	if (tmp == NULL)
	{
		printf("malloc failed\n");
		return ;
	}
	QNode* newNode = tmp;
	newNode->date = x;
	newNode->next = NULL;

	if (pq->head == NULL)
	{
		pq->head = pq->tail = newNode;
	}
	else
	{
		pq->tail->next = newNode;
		pq->tail = newNode;
	}
}
// 出队列
void QueuePop(Queue *pq)
{
	assert(pq);
	assert(pq->head != NULL && pq->tail != NULL);

	if (pq->head->next == NULL)
	{
		free(pq->head);
		pq->head = pq->tail = NULL;
	}
	else
	{
		QNode* HeadNext = pq->head->next;
		free(pq->head);
		pq->head = HeadNext;
	}
}
// 队列判空
bool QueueEmpty(Queue *pq)
{
	assert(pq);

	return pq->head == NULL;
}
// 队列长度
size_t QueueSize(Queue *pq)
{
	assert(pq);

	QNode* cur = pq->head;
	size_t size = 0;
	while (cur)
	{
		++size;
		cur = cur->next;
	}

	return size;
}
// 队列头 数据
QDatetype QueueFront(Queue *pq)
{
	assert(pq);
	assert(pq->head);

	return pq->head->date;
}
// 队列尾 数据
QDatetype QueueBack(Queue *pq)
{
	assert(pq);
	assert(pq->tail);

	return pq->tail->date;
}
