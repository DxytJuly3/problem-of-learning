#define _CRT_SECURE_NO_WARNINGS 1

//#include <stdio.h>
//
//int x = 5, y = 7;
//void swap()
//{
//	int z;
//	z = x;
//	x = y;
//	y = z;
//}
//int main()
//{
//	int x = 3, y = 8;
//	swap();
//	printf("%d,%d\n", x, y);
//
//	return 0;
//}
/*����:
����ȫ�ֱ��� x = 5, y = 7;
main�������ھֲ����� x = 3, y = 8;
main�����е��� swap ���� ��δ����
����ʹ��swap����������ȫ�ֱ���x��y��ֵ
����main��������� x��yδ�ֲ�����
��������ֲ�����x��yԭֵ
�� 3,8
*/




//#define INT_PTR int*
//
//#include <stdio.h>
//typedef int* int_ptr;
//
//int main()
//{
//	INT_PTR a, b;
//	int_ptr c, d;
//
//	return 0;
//}

/*
#define(�궨��)ֻ�Ǽ򵥵��ַ��������������ڱ�������н��У�������Ԥ������̾��Ѿ������
typedef��Ϊ�����ӿɶ��Զ�Ϊ��ʶ������������ƣ�������һ���ķ�װ�ԣ��������Ա�����̵�һ���֣���������ʵ�ʷ����ڴ�ռ䡣

���� #define INT_PTR int* �����ǽ� int* ����һ������
typedef int* int_ptr;	���ǽ�int* ��װ��int_ptr
����ʹ�� INT_PTR a, b;	�� int* a, b; ��ͬ���൱��int* a; int b; ����ʹ a ����Ϊ����ָ��
int_ptr c, d;	���൱��int* c; int* d;		c��d������Ϊ����ָ��
*/






#include <stdio.h>

int main()
{
	int b;
	char c[10];
	scanf("%d%s", &b, c);
	printf("%d\n%s\n", b, c);
	scanf("%d%s", &b, &c);
	printf("%d\n%s\n", b, c);

	return 0;
}

