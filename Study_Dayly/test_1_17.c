#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//
//void revolve_char(char* arr, int arrLen, int k)
//{//传参： 数组名、数组长度、旋转位数
//	for (int i = 0; i < k; i++)
//	{
//		int tmp = *arr;
//		for (int j = 1; j < arrLen; j++)
//		{
//			*(arr + j - 1) = *(arr + j);
//		}
//		*(arr + arrLen - 1) = tmp;
//	}
//}
//
//int main()
//{
//	int k = 0;
//	char arr[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
//	printf("旋转前%s\n输入k:>", arr);
//	scanf("%d", &k);
//	revolve_char(arr, 26, k);
//	printf("%s", arr);
//
//	return 0;
//}

//#include <stdio.h>
//
//int findnum(int (*arr)[5], int row, int col, int k)
//{
//	int i = 0;
//	int j = col - 1;
//
//	while (j >= 0 && i < row)
//	{
//		if (*(*(arr + i) + j) < k)
//			i++;
//		else if (*(*(arr + i) + j) > k)
//			j--;
//		else
//			return k;
//	}
//
//	return 0;
//}
//
//int main()
//{
//	int arr[5][5] = { { 1, 3, 5, 7, 9},
//					  { 2, 4, 6, 8, 10},
//					  { 3, 5, 7, 9, 11},
//					  { 4, 6, 8, 10, 12},
//					  { 5, 7, 9, 11, 13} };
//	int k = 0;
//	scanf("%d", &k);
//	
//	if (findnum(arr, 5, 5, k))
//		printf("Yes!");
//	else
//		printf("No!");
//
//	return 0;
//}

//#include <stdio.h>
//#include <string.h>
//
//int Search_revolve_chars(const char* chars, char* Search_chars)
//{
//	char tmp[1000] = { 0 };
//	strcpy(tmp, chars);
//	strcat(tmp, chars);
//	if (strstr(tmp, Search_chars) == NULL)
//		return 0;
//	else
//		return 1;
//}
//
//int main()
//{
//	char ch1[] = { "ABCDEFG" };
//	char ch2[] = { "DEFGABC" };
//	int ret = Search_revolve_chars(ch1, ch2);
//	printf("%d", ret);
//
//	return 0;
//}

#include <stdio.h>

int cmp_int(const void*e1, const void* e2)
{
	return *(int*)e1 - *(int*)e2;
}

void Swap(char* buf1, char* buf2, int width)
{
	for (int i = 0; i < width; i++)
	{
		int tmp = *buf1;
		*buf1 = *buf2;
		*buf2 = tmp;
		buf1++;
		buf2++;
	}
}

void bubble_sort(void* base, int sz, int width, int (*cmp)(const void* e1, const void* e2))
{
	for (int i = 0; i < sz - 1; i++)
	{
		for (int j = 0; j < sz - 1; j++)
		{
			if (cmp(((char*)base + j * width), ((char*)base + (j + 1) * width)) > 0)
			{
				Swap( ((char*)base + j * width), ((char*)base + (j + 1) * width), width);
			}
		}
	}
}

void print(int* arr, int sz)
{
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", *(arr + i));
	}
}

int main()
{
	int arr[] = { 9, 2, 3, 6, 1, 7 };
	bubble_sort(arr, 6, sizeof(arr[0]), cmp_int);
	print(arr, 6);

	return 0;
}



//void Swap(char* buf1, char* buf2, int width)
//{
//	int i = 0;
//	for (i = 0; i < width; i++)
//	{
//		char tmp = *buf1;
//		*buf1 = *buf2;
//		*buf2 = tmp;
//		buf1++;
//		buf2++;
//	}
//}
//
//void bubble_sort(void* base, int sz, int width, int(*cmp)(const void*e1, const void*e2))
//{
//	int i = 0;
//	for (i = 0; i < sz - 1; i++)
//	{
//		int j = 0;
//		for (j = 0; j < sz - 1 - i; j++)
//		{
//			//if (arr[j] > arr[j + 1])
//			if(cmp((char*)base + j * width, (char*)base + (j + 1) * width)>0)
//			{
//				//两个元素的交换
//				Swap((char*)base + j * width, (char*)base + (j + 1) * width, width);
//			}
//		}
//	}
//}