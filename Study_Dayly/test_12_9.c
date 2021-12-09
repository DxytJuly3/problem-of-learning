#define _CRT_SECURE_NO_WARNINGS 1

//写函数打印数组
//#include <stdio.h>
//
//void print(int* arr, int sz)
//{
//	int i = 0;
//	for (i = 0; i < sz; i++)
//	{
//		printf("%d ", *(arr+i));
//	}
//}
//
//int main()
//{
//	int arr[] = { 1,2,3,4,5,6,7,8,9,0,3,71,1,54,21,21,4,5,23 };
//	int sz = sizeof(arr) / sizeof(arr[0]);
//	print(arr, sz);
//
//	return 0;
//}


// 逆序字符串
//#include <stdio.h>
//#include <string.h>
//
//void back_chars(char* s)
//{
//    char* left = s;
//    char* right = left + strlen(s) - 1;
//    while (left < right)
//    {
//        int tmp = *left;
//        *left = *right;
//        *right = tmp;
//        left++;
//        right--;
//    }
//}
//int main()
//{
//    char s[100] = "0";
//    scanf("%s", s);
//    back_chars(s);
//    printf("%s", s);
//
//    return 0;
//}


// 求 a + aa + aaa + aaaa + aaaaa 
//#include <stdio.h>
//#include <math.h>
//
//int main()
//{
//	int a = 0;
//	scanf("%d", &a);
//	int i = 0;
//	int s = a;
//	int sum = 0;
//	for(i = 0; i < 5; i++)
//	{ 
//		sum += a;
//		a = a * 10 + s;
//	}
//	printf("%d", sum);
//
//	return 0;
//}

// 水仙花数
//#include <stdio.h>
//#include <math.h>
//
//int main()
//{
//	int i = 0;
//	int j = 0;
//	int g = 0;
//	for (i = 1; i <= 100000; i++)
//	{
//		int count = 1;
//		int sum = 0;
//		int x = i;		//防止 i 改变，设置中间变量
//		while (x /= 10)
//		{
//			count++;	//计算位数
//		}
//		x = i;			//在计算位数中，x 改变了，需重新赋为 i
//		for (j = 0; j < count; j++)
//		{
//			g = x % 10;		//求个位
//			sum = sum + pow(g,count);	//求个位的n 次方
//			x /= 10;		//每次 减少一位
//		}
//		if (sum == i)
//		{
//			printf("%d ", i);		//如果 i 各位 的 n 次方之和 与 i 相等，则为水仙花数
//		}
//	}
//
//	return 0;
//}


//菱形输出
#include <stdio.h>

int main()
{
	int i = 0;
	int j = 0;
	int n = 0;
	scanf("%d", &n);
	for (i = 1; i < n+1; i++)
	{
		for (j = 0; j < n-i; j++)
		{
			printf("  ");
		}
		for (j = 0; j < 2*i-1; j++)
		{
			printf("* ");
		}
		printf("\n");
	}
	for (i = 1; i < n; i++)
	{
		for (j = 0; j < i; j++)
			printf("  ");
		for (j = 1; j < 2*(n-i); j++)
			printf("* ");
		printf("\n");
	}

	return 0;
}