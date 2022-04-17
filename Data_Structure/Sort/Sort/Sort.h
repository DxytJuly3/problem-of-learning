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
// ≤Â»Î≈≈–Ú
void insertSort(int* a, int size);
// √∞≈›≈≈–Ú
void bubbleSort(int* a, int size);
// œ£∂˚≈≈–Ú
void shellSort(int* a, int size);
// —°‘Ò≈≈–Ú
void selectSort(int* a, int size);
// hoareøÏ≈≈
void hoareQuickSort(int* a, int begin, int end);

void HeapSort(int *data, size_t size);
