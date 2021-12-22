#include <stdio.h>
//KiKi得到了一个n行m列的矩阵，现在他想知道第x行第y列的值是多少，请你帮助他完成这个任务。
//数据范围：1 <= n,m <= 5 ，矩阵中的值满足 1 <= val <= 25
int main()
{
	int n = 0;
	int m = 0;
	int arr[5][5] = { 0 };
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			scanf("%d", &arr[i][j]);
	}
	int x = 0;
	int y = 0;
	scanf("%d%d", &x, &y);
	printf("%d", arr[x - 1][y - 1]);

	return 0;
}