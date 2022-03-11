#define _CRT_SECURE_NO_WARNINGS 1

#include "SeqList.h"

// 顺序表容量检查
void SeqListCheckCapacity(SeqList* psl)
{
	assert(psl);

	if (psl->size == psl->capacity)
	{
		size_t newCapacity = psl->capacity == 0 ? 4 : psl->capacity * 2;
		SLDateType *tmp = (SLDateType*)realloc(psl->s, sizeof(SLDateType) * newCapacity);
		if (tmp != NULL)
		{
			psl->s = tmp;
			psl->capacity = newCapacity;
		}
		else
		{
			printf("realloc failed\n");
		}
	}
}

// 顺序表初始化
void SeqListInit(SeqList *psl)
{
	assert(psl);

	psl->s = NULL;
	psl->size = 0;
	psl->capacity = 0;
}

// 顺序表尾插
void SeqListPushBack(SeqList *psl, SLDateType x)
{
	assert(psl);

	SeqListCheckCapacity(psl);

	psl->s[psl->size] = x;
	psl->size++;
}

// 顺序表尾删
void SeqListPopBack(SeqList *psl)
{
	assert(psl);
	
	if (psl->size > 0)		// 顺序表需要有内容
	{
		psl->size--;
	}
}

// 顺序表打印
void SeqListPrint(SeqList *psl)
{
	assert(psl);

	for (int i = 0; i < psl->size; i++)
	{
		printf("%d ", psl->s[i]);
	}
	printf("\n");
}

// 顺序表前插
void SeqListPushFront(SeqList *psl, SLDateType x)
{
	assert(psl);

	SeqListCheckCapacity(psl);

	for (int i = psl->size - 1; i >= 0; i--)
	{
		psl->s[i+1] = psl->s[i];
	}
	/*
	int end = psl->size - 1;
	while(end >= 0)
	{
		psl->s[end+1] = psl->s[end];
		end--;
	}
	*/

	psl->s[0] = x;
	psl->size++;
}

// 顺序表前删
void SeqListPopFront(SeqList *psl)
{
	assert(psl);

	if (psl->size > 0)
	{
		for (int i = 1; i < psl->size; i++)
		{
			psl->s[i - 1] = psl->s[i];
		}
		/*
		int begin = 1;
		while( begin < psl->size)
		{
			psl->s[begin - 1] = psl->s[begin];
			begin++;
		}
		*/

		psl->size--;
	}
}

// 顺序表插入(在pos位置插入x)
void SeqListInsert(SeqList *psl, size_t pos, SLDateType x)
{
	assert(psl);

	SeqListCheckCapacity(psl);

	for (int i = psl->size - 1; i >= pos - 1; i--)
	{
		psl->s[i + 1] = psl->s[i];
	}
	psl->s[pos - 1] = x;
	psl->size++;
}