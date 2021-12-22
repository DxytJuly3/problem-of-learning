<<<<<<< HEAD
#include <stdio.h>
//有一个有序数字序列，从小到大排序，将一个新输入的数插入到序列中，保证插入新数后，序列仍然是升序。
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
		if (arr[i] <= num && num <= arr[i + 1])
		{
			for (int j = 0; j < n - i; j++)
			{
				arr[n - j + 1] = arr[n - j];
			}
			arr[i + 1] = num;
			break;
		}
        if(num < arr[0])
        {
            for (int j = n; j >= 0; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[0] = num;
        }
		else if (num > arr[n - 1])
			arr[n] = num;
	}
    for(i = 0; i <= n; i++)
        printf("%d ", arr[i]);

	return 0;
=======
#include <stdio.h>
//有一个有序数字序列，从小到大排序，将一个新输入的数插入到序列中，保证插入新数后，序列仍然是升序。
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
		if (arr[i] <= num && num <= arr[i + 1])
		{
			for (int j = 0; j < n - i; j++)
			{
				arr[n - j + 1] = arr[n - j];
			}
			arr[i + 1] = num;
			break;
		}
        if(num < arr[0])
        {
            for (int j = n; j >= 0; j--)
			{
				arr[j + 1] = arr[j];
			}
			arr[0] = num;
        }
		else if (num > arr[n - 1])
			arr[n] = num;
	}
    for(i = 0; i <= n; i++)
        printf("%d ", arr[i]);

	return 0;
>>>>>>> dbaaf41c9355094a1477afd349ca43a2a26c6542
}