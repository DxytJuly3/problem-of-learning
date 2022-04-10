#pragma once 

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int HPDataType;

typedef struct Heap
{
	HPDataType* data;
	size_t size;
	size_t capacity;
}Heap;

// 堆 初始化
void HeapInit(Heap* php);
// 堆 销毁
void HeapDestroy(Heap* php);
// 堆 插入数据
void HeapPush(Heap* php, HPDataType x);
// 堆 删除数据
void HeapPop(Heap* php);
// 堆 数据打印
void HeapPrint(Heap* php);
// 判空
bool HeapEmpty(Heap* php);
// 堆的根的数据
HPDataType HeapTop(Heap* php);
// 堆大小
size_t HeapSize(Heap* php);
// 排序 降序
void HeapSort(int *a, size_t size);
// Top-K 问题 思路
void PrintTopK(int* a, int n, int k);