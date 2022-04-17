#define _CRT_SECURE_NO_WARNINGS 1

#include "Sort.h"

int main()
{

	int arr[] = { 9, 33, 6, 41, 32, 45, 5, 123, 43, 9, 54, 6, 1, 34, 7, 47, 2, 5, 236, 6 };
	hoareQuickSort(arr, 0, 19);
	printArr(arr, 20);

	return 0;
}