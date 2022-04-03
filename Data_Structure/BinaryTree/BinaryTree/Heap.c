#define _CRT_SECURE_NO_WARNINGS 1

#include "Heap.h"

// �� ��ʼ��
void HeapInit(Heap* php)
{
	assert(php);

	php->data = NULL;
	php->size = php->capacity = 0;
}
// �� ����
void HeapDestroy(Heap* php)
{
	assert(php);

	free(php->data);
	php->data = NULL;
	php->size = php->capacity = 0;
}
// �������ݽ���
void swap(HPDataType* px, HPDataType* py)
{
	HPDataType tmp = px;
	*px = *py;
	*py = tmp;
}
// �����ϵ�����ȷ������ѣ�
void AdjustUp(HPDataType* data, size_t child)
{
	assert(data);

	while (child > 0)
	{
		size_t parent = (child - 1) / 2;
		if (data[child] > data[parent])
		{
			swap(&data[child], &data[parent]);
			child = parent;
		}
		else
			break;
	}
}
// ��������ݲ���
void HeapPush(Heap* php, HPDataType x)
{
	assert(php);

	if (php->size == php->capacity)
	{
		size_t newCapacity = php->capacity == 0 ? 4 : 2 * php->capacity;
		HPDataType* tmp = (HPDataType*)malloc(newCapacity * sizeof(HPDataType));
		if (tmp == NULL)
		{
			printf("malloc failed!\n");
			exit(-1);
		}

		php->data = tmp;
		php->capacity = newCapacity;
	}

	php->data[php->size] = x;
	++php->size;

	AdjustUp(php->data, php->size - 1);
}

void AdjustDown(HPDataType* data, size_t size, size_t root)
{
	assert(data);

	size_t parent = root;
	size_t child = parent * 2 + 1;
	while (child < size)
	{
		if (child + 1 && data[child] < data[child + 1])
		{
			++child;
		}

		if (data[parent] < data[child])
		{
			swap(&data[parent], &data[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

// ���������ɾ�����Ӹ���
void HeapPop(Heap* php)
{
	assert(php);
	assert(php->size > 0);

	swap(&php->data[0], &php->data[php->size - 1]);
	--php->size;

	AdjustDown(php->data, php->size, 0);
}