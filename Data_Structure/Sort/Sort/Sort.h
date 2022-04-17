#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <assert.h>

typedef int HPDataType;

typedef struct Heap
{
	HPDataType* data;
	size_t size;
	size_t capacity;
}Heap;

void AdjustDown(HPDataType* data, size_t size, size_t root);

void printArr(int *a, int size);

void Swap(int* a, int* b);
// ��������
void insertSort(int* a, int size);
// ð������
void bubbleSort(int* a, int size);
// ϣ������
void shellSort(int* a, int size);
// ѡ������
void selectSort(int* a, int size);
// hoare����
void hoareQuickSort(int* a, int begin, int end);

void HeapSort(int *data, size_t size);
