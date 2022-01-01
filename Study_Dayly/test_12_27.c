#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

int main()
{
	int n = 0;
	int m = 0;
	scanf("%d%d", &n, &m);
	int arr[10][10] = { 0 };
	int times = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			scanf("%d", &arr[i][j]);
		}
	}
	scanf("%d", &times);
	for (int i = 0; i < times; i++)
	{
		char t = 0;
		int c_r1 = 0;
		int c_r2 = 0;
		getchar();
		scanf("%c", &t);
		scanf("%d%d", &c_r1, &c_r2);
		if (t == 'c')
		{
			for (int j = 0; j < m; j++)
			{
				int tmp = arr[j][c_r1 - 1];
				arr[j][c_r1 - 1] = arr[j][c_r2 - 1];
				arr[j][c_r2 - 1] = tmp;
			}
		}
		else if (t == 'r')
		{
			for (int j = 0; j < m; j++)
			{
				int tmp = arr[c_r1 - 1][j];
				arr[c_r1 - 1][j] = arr[c_r2 - 1][j];
				arr[c_r2 - 1][j] = tmp;
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}