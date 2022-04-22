#define _CRT_SECURE_NO_WARNINGS 1

#include "Sort.h"

void TestOP()
{
	srand(time(0));
	const int N = 10000000;
	int* a1 = (int*)malloc(sizeof(int)*N);
	int* a2 = (int*)malloc(sizeof(int)*N);
	int* a3 = (int*)malloc(sizeof(int)*N);
	int* a4 = (int*)malloc(sizeof(int)*N);
	int* a5 = (int*)malloc(sizeof(int)*N);
	int* a6 = (int*)malloc(sizeof(int)*N);
	int* a7 = (int*)malloc(sizeof(int)*N);

	for (int i = 0; i < N; ++i)
	{
		a1[i] = rand();
		a2[i] = a1[i];
		a3[i] = a1[i];
		a4[i] = a1[i];
		a5[i] = a1[i];
		a6[i] = a1[i];
		a7[i] = a1[i];
	}

	int begin1 = clock();
	//InsertSort(a1, N);
	int end1 = clock();

	int begin2 = clock();
	//ShellSort(a2, N);
	int end2 = clock();

	int begin7 = clock();
	//BubbleSort(a7, N);
	int end7 = clock();

	int begin3 = clock();
	//SelectSort(a3, N);
	int end3 = clock();

	int begin4 = clock();
	//HeapSort(a4, N);
	int end4 = clock();

	int begin5 = clock();
	midQuickSort(a5, 0, N - 1);
	int end5 = clock();

	int begin6 = clock();
	non_recursive_QuickSort(a6, 0, N - 1);
	int end6 = clock();

	printf("InsertSort:%d\n", end1 - begin1);
	printf("ShellSort:%d\n", end2 - begin2);
	printf("BublleSort:%d\n", end7 - begin7);

	printf("SelectSort:%d\n", end3 - begin3);
	printf("HeapSort:%d\n", end4 - begin4);
	printf("midQuickSort:%d\n", end5 - begin5);
	printf("non_recursive_QuickSort:%d\n", end6 - begin6);

	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(a5);
	free(a6);
	free(a7);
}

//int main()
//{
//	//TestInsertSort();
//	//TestBubbleSort();
//	//TestShellSort();
//	//TestSelectSort();
//	//TestQuickSort();
//
//	//TestOP();
//
//	return 0;
//}
//
int main()
{

	int arr[] = { 9, 33, 6, 41, 32, 45, 5, 43, 9, 6, 1, 34, 7, 47, 2, 5, 6 };
	margeSort(arr, 17);
	printArr(arr, 17);

	return 0;
}