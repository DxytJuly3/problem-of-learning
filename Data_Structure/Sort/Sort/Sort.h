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
// 插入排序
void insertSort(int* a, int size);
// 冒泡排序
void bubbleSort(int* a, int size);
// 希尔排序
void shellSort(int* a, int size);
// 选择排序
void selectSort(int* a, int size);
// 快排
void quickSort(int* a, int begin, int end);
// 三数取中 优化快排
void midQuickSort(int* a, int begin, int end);
// 小区间优化快排
void minQuickSort(int* a, int begin, int end);
// 非递归快排
void non_recursive_QuickSort(int* a, int begin, int end);
// 堆排序
void HeapSort(int *data, size_t size);

void margeSort(int* a, int size);