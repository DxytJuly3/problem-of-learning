#define _CRT_SECURE_NO_WARNINGS 1

#include "Stack.h"
#include <time.h>
#include <string.h>


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
// ����
void quickSort(int* a, int begin, int end);
// ����ȡ�� �Ż�����
void midQuickSort(int* a, int begin, int end);
// С�����Ż�����
void minQuickSort(int* a, int begin, int end);
// �ǵݹ����
void non_recursive_QuickSort(int* a, int begin, int end);
// ������
void HeapSort(int *data, size_t size);

void margeSort(int* a, int size);