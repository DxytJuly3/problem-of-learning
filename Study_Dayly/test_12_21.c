#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//
//int main()
//{
//    int n = 0;
//    scanf("%d", &n);
//    int i = 0;
//    int arr[50] = { 0 };
//    int flag1 = 0;
//    int flag2 = 0;
//    for (i = 0; i < n; i++)
//    {
//        scanf("%d", &arr[i]);
//    }
//    for (i = 0; i < n; i++)
//    {
//        if (arr[i] < arr[i + 1])
//            flag1++;
//        else
//            break;
//    }
//    for (i = 0; i < n; i++)
//    {
//        if (arr[i] > arr[i + 1])
//            flag2++;
//        else
//            break;
//    }
//    if (flag1 == n - 1 || flag2 == n)
//        printf("sorted\n");
//    else
//        printf("unsorted\n");
//
//    return 0;
//}

#include <stdio.h>

int main()
{
	int n = 0;
	scanf("%d", &n);
	int i = 0;
	int arr[51] = { 0 };
	int num = 0;
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}
	scanf("%d", &num);
	for (i = 0; i < n; i++)
	{
		if (arr[i] <= num && num <= arr[i + 1] || num < arr[0])
		{
			for (int j = 0; j <= n - i; j++)
			{
				arr[n - j + 1] = arr[n - j];
			}
			arr[i + 1] = num;
			break;
		}
		else if (num > arr[n - 1])
			arr[n] = num;
	}

	return 0;
}