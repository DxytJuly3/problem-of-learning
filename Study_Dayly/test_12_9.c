#define _CRT_SECURE_NO_WARNINGS 1

//д������ӡ����
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


// �����ַ���
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


// �� a + aa + aaa + aaaa + aaaaa 
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

// ˮ�ɻ���
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
//		int x = i;		//��ֹ i �ı䣬�����м����
//		while (x /= 10)
//		{
//			count++;	//����λ��
//		}
//		x = i;			//�ڼ���λ���У�x �ı��ˣ������¸�Ϊ i
//		for (j = 0; j < count; j++)
//		{
//			g = x % 10;		//���λ
//			sum = sum + pow(g,count);	//���λ��n �η�
//			x /= 10;		//ÿ�� ����һλ
//		}
//		if (sum == i)
//		{
//			printf("%d ", i);		//��� i ��λ �� n �η�֮�� �� i ��ȣ���Ϊˮ�ɻ���
//		}
//	}
//
//	return 0;
//}


//�������
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