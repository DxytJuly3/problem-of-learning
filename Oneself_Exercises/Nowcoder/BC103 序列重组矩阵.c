#include <stdio.h>
//KiKi现在得到一个包含n*m个数的整数序列，现在他需要把这n*m个数按顺序规划成一个n行m列的矩阵并输出，请你帮他完成这个任务。
int main()
{
	int n = 0;
	int m = 0;
	int arr[100] = { 0 };
    scanf("%d%d", &n, &m);
	for (int i = 0; i < n * m; i++)
	{
		scanf("%d", &arr[i]);
	}
	for (int i = 1; i <= n * m; i++)
	{
		printf("%d ", arr[i-1]);
		if (i % m == 0)
			printf("\n");
	}

	return 0;
}