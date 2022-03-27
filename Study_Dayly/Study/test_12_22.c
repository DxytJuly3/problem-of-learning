#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//
//int main()
//{
//    int arr[1000] = { 0 };
//    int i = 0;
//    int n = 0;
//    scanf("%d", &n);
//    for (i = 0; i < n; i++)
//    {
//        int tmp = 0;
//        int flag = 0;
//        scanf("%d", &tmp);
//        for (int j = 0; j < i; j++)
//        {
//            if (tmp == arr[j])
//                flag++;
//        }
//        if (flag == 0)
//            arr[i] = tmp;
//    }
//    for (i = 0; i < n; i++)
//    {
//        if (arr[i] != 0)
//            printf("%d ", arr[i]);
//    }
//
//    return 0;
//}

//#include <stdio.h>
//
//void bubble_sort(int* arr, int n)
//{
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < n - 1; i++)
//	{
//		int* arrn = arr;
//		for (j = i; j < n - 1; j++)
//		{
//			if (*arrn > *(arrn + 1))
//			{
//				int tmp = *(arrn + 1);
//				*(arrn + 1) = *arrn;
//				*arrn = tmp;
//			}
//			arrn++;
//		}
//	}
//}
//
//int main()
//{
//	int n = 0;
//	int m = 0;
//	scanf("%d%d", &n, &m);
//	int arr[2000] = { 0 };
//	int i = 0;
//	for (i = 0; i < n + m; i++)
//	{
//		scanf("%d", &arr[i]);
//	}
//	bubble_sort(arr, n + m);
//	for (i = 0; i < n + m; i++)
//	{
//		printf("%d ", arr[i]);
//	}
//
//	return 0;
//}

//#include <stdio.h>
//
//int main()
//{
//	double score[5][6] = { 0 };
//	int i = 0;
//	int j = 0;
//	for (i = 0; i < 5; i++)
//	{
//		for (j = 0; j < 5; j++)
//			scanf("%lf", &score[i][j]);
//	}
//	for (i = 0; i < 5; i++)
//	{
//		double sum = 0;
//		for (j = 0; j < 5; j++)
//		{
//			sum += score[i][j];
//		}
//		score[i][5] = sum;
//	}
//	for (i = 0; i < 5; i++)
//	{
//		for (j = 0; j < 6; j++)
//		{
//			printf("%.1lf ", score[i][j]);
//		}
//		printf("\n");
//	}
//
//	return 0;
//}

//#include <stdio.h>

//int main()
//{
//	int n = 0;
//	int m = 0;
//	int arr[5][5] = { 0 };
//	int i = 0;
//	int j = 0;
//	scanf("%d%d", &n, &m);
//	for (i = 0; i < n; i++)
//	{
//		for (j = 0; j < m; j++)
//			scanf("%d", &arr[i][j]);
//	}
//	int x = 0;
//	int y = 0;
//	scanf("%d%d", &x, &y);
//	printf("%d", arr[x - 1][y - 1]);
//
//	return 0;
//}

#include <stdio.h>

int main()
{
	int n = 0;
	int m = 0;
	int arr[20] = { 0 };
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n * m; i++)
	{
		scanf("%d", &arr[i]);
	}
	for (int i = 0; i < n * m; i++)
	{
		printf("%d ", arr[i]);
		if (i % m == 0)
			printf("\n");
	}

	return 0;
}