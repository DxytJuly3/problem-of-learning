#define _CRT_SECURE_NO_WARNINGS 1

#include "SeqList.h"

// 顺序表容量检查
void SeqListCheckCapacity(SeqList *psl)
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

	/*SeqListCheckCapacity(psl);

	psl->s[psl->size] = x;
	psl->size++;*/

	SeqListInsert(psl, psl->size, x);		//直接调用 顺序表插入 插入位置为 psl->size
}

// 顺序表尾删
void SeqListPopBack(SeqList *psl)
{
	assert(psl);
	
	//if (psl->size > 0)		// 顺序表需要有内容
	//{
	//	psl->size--;
	//}

	SeqListErase(psl, psl->size - 1);		// 直接调用 pos 位置删除
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

	//SeqListCheckCapacity(psl);

	//for (int i = psl->size - 1; i >= 0; i--)
	//{
	//	psl->s[i+1] = psl->s[i];
	//}
	///*
	//int end = psl->size - 1;
	//while(end >= 0)
	//{
	//	psl->s[end+1] = psl->s[end];
	//	end--;
	//}
	//*/

	//psl->s[0] = x;
	//psl->size++;

	SeqListInsert(psl, 0, x);			// 直接调用 pos 位置插入函数
}

// 顺序表前删
void SeqListPopFront(SeqList *psl)
{
	assert(psl);

	//if (psl->size > 0)
	//{
	//	for (int i = 1; i < psl->size; i++)
	//	{
	//		psl->s[i - 1] = psl->s[i];
	//	}
	//	/*
	//	int begin = 1;
	//	while( begin < psl->size)
	//	{
	//		psl->s[begin - 1] = psl->s[begin];
	//		begin++;
	//	}
	//	*/

	//	psl->size--;
	//}

	SeqListErase(psl, 0);			// 直接调用 pos 位置删除函数
}

// 顺序表插入(在pos位置插入x)
void SeqListInsert(SeqList *psl, size_t pos, SLDateType x)
{
	assert(psl);

	//assert(pos < psl->size);
	if (pos > psl->size)
	{// 检测 pos 是否越界
		printf("pos 越界：pos = %d", pos);
		return;
	}

	SeqListCheckCapacity(psl);

	/*int end = psl->size - 1;
	while (end >= (int)pos)				//pos 强转为 int类型，防止 psl->size === 0时，end === -1 在比较的时候被整型提升为 size_t 类型。
	{
		psl->s[end] = psl->s[end + 1];
		end--;
	}*/
	size_t end = psl->size;				//这种方法也可以防止 以上情况发生，直接防止 end 被赋予负数，因为 psl->size 恒大于 0 
	while (end > pos)
	{
		psl->s[end] = psl->s[end - 1];
		end--;
	}
	
	psl->s[pos] = x;
	psl->size++;
}

// 删除 pos 位置的数据
void SeqListErase(SeqList *psl, size_t pos)
{
	assert(psl);

	//assert(pos < psl->size);
	if (pos >= psl->size)
	{// 检测 pos 是否越界
		printf("pos 越界：pos = %d", pos);
		return;
	}

	size_t begin = pos + 1;
	while (begin < psl->size)
	{
		psl->s[begin - 1] = psl->s[begin];
		begin++;
	}

	psl->size--;
}

// 顺序表查找
int SeqListFind(SeqList *psl, SLDateType x)
{
	for (size_t i = 0; i < psl->size; i++)
	{
		if (psl->s[i] == x)
		{
			return i;
		}
	}

	return -1;
}

// 顺序表销毁
void SeqListDestory(SeqList *psl)
{
	assert(psl);

	free(psl->s);
	psl->s = NULL;
	psl->size = 0;
	psl->capacity = 0;
}