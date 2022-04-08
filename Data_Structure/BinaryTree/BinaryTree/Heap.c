#define _CRT_SECURE_NO_WARNINGS 1

#include "Heap.h"

// �ѵĴ�ӡ
void HeapPrint(Heap* php)
{
	assert(php);

	for (int i = 0; i < php->size; i++)
	{
		printf("%d ", php->data[i]);
	}
}

// �� ��ʼ��
void HeapInit(Heap* php)
{
	assert(php);

	php->data = NULL;
	php->capacity = php->size = 0;
}
// �� ����
void HeapDestroy(Heap* php)
{
	assert(php);

	free(php->data);
	php->data = NULL;
	php->capacity = php->size = 0;
}
// �������ݽ���
void swap(HPDataType* px, HPDataType* py)
{
	HPDataType tmp = *px;
	*px = *py;
	*py = tmp;
}

// �����ϵ�����ȷ������ѣ�
void AdjustUp(HPDataType* data, size_t child)
{
	assert(data);

	// ���ӽڵ�ȸ��׽ڵ�� �ͽ���λ��
	while (child > 0)
	{
		size_t parent = (child - 1) / 2;
		if (data[child] > data[parent])
	  //if (data[child] < data[parent]) �������ϵ�������С����
		{
			swap(&data[child], &data[parent]);
			child = parent;
		}
		else
		{
			break;
		}
	}

}
// ���ݲ��� ������ѣ�
void HeapPush(Heap* php, HPDataType x)
{
	assert(php);

	if (php->size == php->capacity)
	{
		HPDataType newCapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		HPDataType* tmp = (HPDataType*)realloc(php->data, sizeof(HPDataType)* newCapacity);
		if (tmp == NULL)
		{
			printf("realloc failed!\n");
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
	// ���µ�������Ҫ�Աȸ��׽ڵ�ͺ��ӽڵ�Ĵ�С
	// ������׽ڵ�С�ں��ӽڵ����Ҫ����λ��
	// ���Ǹ��׽ڵ�һ������»����������ӽڵ�  ����Ҫ�жϳ��������ӽڵ��� ������Ǹ����ӽڵ� �� ���׽ڵ���н���
	// Ϊ�˷����ж� ����ֱ�Ӽ��� ���ӽڵ���Ǵ�ĺ��ӽڵ�
	// ������ӽڵ㲻�Ǵ�ĺ��ӽڵ�  �����Һ��ӽ������Ϊ��ĺ��ӽڵ� 
	// Ȼ�����ж� ���׽ڵ�������ĺ��ӽڵ�Ĵ�С
	// Ȼ���ٽ��н���

	// ѭ�������������� ��child > size   �����ӽڵ�λ�ô���ʵ��ӵ�нڵ�����ʱֹͣ
	size_t parent = root;
	size_t child = parent * 2 + 1; 
	while (child < size)
	{
		// �ж� ��ĺ��ӽڵ��Ƿ���ȷ
		if (child + 1 <= size && data[child] < data[child + 1])
		{
			++child;
		}

		// ���׽ڵ�С �� ����
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

// ����ɾ��������ѣ�
void HeapPop(Heap* php)
{//�Ӷѵĸ�ɾ������ÿ��ɾ�� ɾ�����Ǹ�
	assert(php);
	assert(php->size > 0);
	// ��һ��˼·������ֱ��ɾ����
	// ���� �� ���һ��Ҷ�ӽڵ㽻��λ�� Ȼ�� size--��ʹԭ���ڵ����ݴӶ�����ʧ
	// ��ʱ �Ѳ��Ǵ���ѣ���Ϊ���һ��Ҷ�ӽڵ㱻�������˸���λ�ã�������Ҫ�Ѵ�ʱ�ĸ��ڵ����µ���������λ��

	swap(&php->data[0], &php->data[php->size - 1]);
	php->size--;

	AdjustDown(php->data, php->size, 0);
}

// �п�
bool HeapEmpty(Heap* php)
{
	assert(php);

	return php->size == 0;
}

// �ѵĸ�������
HPDataType HeapTop(Heap* php)
{
	assert(php);
	assert(php->size > 0);

	return php->data[0];
}

// �Ѵ�С
size_t HeapSize(Heap* php)
{
	assert(php);

	return php->size;
}

// ����
void HeapSort(int *data, size_t size)
{
	assert(data);

	Heap hp;
	HeapInit(&hp);
	for (int i = 0; i < size; i++)
	{
		HeapPush(&hp, data[i]);		// ����Ѿͽ���С���Ѿ�����
	}

	size_t j = 0;
	while (!HeapEmpty(&hp))
	{
		data[j++] = HeapTop(&hp);
		HeapPop(&hp);
	}

	HeapDestroy(&hp);
}