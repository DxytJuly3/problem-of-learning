#include <stdio.h>
//给出两幅相同大小的黑白图像（用0-1矩阵）表示，求它们的相似度。若两幅图像在相同位置上的像素点颜色相同，则称它们在该位置具有相同的像素点。
//两幅图像的相似度定义为相同像素点数占总像素点数的百分比。
int main()
{
	int m = 0;
	int n = 0;
	int arr1[100][100] = { 0 };
	int arr2[100][100] = { 0 };
	scanf("%d%d", &m, &n);
	int i = 0;
	int j = 0;
	int count = 0;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			scanf("%d", &arr1[i][j]);
		}
	}
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			scanf("%d", &arr2[i][j]);
		}
	}
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (arr1[i][j] == arr2[i][j])
				count++;
		}
	}
	printf("%.2lf", (double)count / (m * n) * 100 );

	return 0;
}