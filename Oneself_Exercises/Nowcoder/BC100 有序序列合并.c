#include <stdio.h>
//输入两个升序排列的序列，将两个序列合并为一个有序序列并输出。
void bubble_sort(int* arr, int n)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < n - 1; i++)
	{
		int* arrn = arr;
		for (j = i; j < n - 1; j++)
		{
			if (*arrn > *(arrn + 1))
			{
				int tmp = *(arrn + 1);
				*(arrn + 1) = *arrn;
				*arrn = tmp;
			}
			arrn++;
		}
	}
}

int main()
{
	int n = 0;
	int m = 0;
	scanf("%d%d", &n, &m);
	int arr[2000] = { 0 };
	int i = 0;
	for (i = 0; i < n + m; i++)
	{
		scanf("%d", &arr[i]);
	}
	bubble_sort(arr, n + m);
	for (i = 0; i < n + m; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}