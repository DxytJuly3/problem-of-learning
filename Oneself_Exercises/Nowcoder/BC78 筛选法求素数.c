#include <stdio.h>
//用筛选法求n以内的素数。筛选法求解过程为：
//将2~n之间的正整数放在数组内存储，将数组中2之后的所有能被2整除的数清0，再将3之后的所有能被3整除的数清0 
//以此类推，直到n为止。数组中不为0 的数即为素数。
void arr_Sift(int* arr, int i, int n)
{
	int j = 0;
	for (j = 1; j < n; j++)
	{
		if (arr[j] % i == 0 && arr[j] != i)
		{
			arr[j] = 0;
		}
	}
}

int main()
{
	int n = 0;
	int arr[100] = { 0 };
	int count = 0;
	while (scanf("%d", &n) != EOF)
	{
		int i = 0;
		for (i = 0; i < n; i++)
		{
			arr[i] = i + 1;
		}
		for (i = 1; i < n; i++)
		{
			arr_Sift(arr, i + 1, n);
		}
		for (i = 1; i < n; i++)
		{
			if (arr[i] != 0)
				printf("%d ", arr[i]);
			else if (arr[i] == 0)
				count++;
		}
		printf("\n%d\n", count);
	}


	return 0;
}
