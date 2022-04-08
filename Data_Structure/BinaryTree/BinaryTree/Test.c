#define _CRT_SECURE_NO_WARNINGS 1

#include "Heap.h"

int main()
{
	//Heap hp;
	//HeapInit(&hp);
	//HeapPush(&hp, 5);
	//HeapPush(&hp, 9);
	//HeapPush(&hp, 2);
	//HeapPush(&hp, 6);
	//HeapPush(&hp, 9);
	//HeapPush(&hp, 1);
	//HeapPush(&hp, 7);
	//HeapPush(&hp, 4);
	//HeapPush(&hp, 3);
	//HeapPrint(&hp);
	//printf("\n");

	//HeapPop(&hp);
	//HeapPrint(&hp);
	//printf("\n");

	//HeapPop(&hp);
	//HeapPrint(&hp);
	//printf("\n");

	//HeapPop(&hp);
	//HeapPrint(&hp);
	//printf("\n");

	int a[] = { 1, 5, 2, 67, 78, 23, 67, 43, 6, 2, 6, 3, 34 };
	HeapSort(a, 13);
	for (int i = 0; i < 13; i++)
	{
		printf("%d ", a[i]);
	}

	return 0;
}