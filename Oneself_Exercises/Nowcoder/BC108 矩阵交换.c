#include <stdio.h>
//第一行包含两个整数n和m，表示一个矩阵包含n行m列，用空格分隔。 (1≤n≤10,1≤m≤10)
//从2到n+1行，每行输入m个整数，用空格分隔，共输入n*m个数，表示第一个矩阵中的元素。
//接下来一行输入k，表示要执行k次操作（1≤k≤5）。
//接下来有k行，每行包括一个字符t和两个数a和b，中间用空格格分隔，t代表需要执行的操作
//当t为字符'r'时代表进行行变换，当t为字符'c'时代表进行列变换，a和b为需要互换的行或列（1≤a≤b≤n≤10，1≤a≤b≤m≤10）。


提示：当t为别的字符时不需要处理
int main()
{
	int n = 0;
	int m = 0;
	scanf("%d%d", &n, &m);
	int arr[10][10] = {0};
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