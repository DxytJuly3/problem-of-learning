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
/*解析:
存在全局变量 x = 5, y = 7;
main函数存在局部变量 x = 3, y = 8;
main函数中调用 swap 函数 但未传参
所以使用swap函数交换两全局变量x、y的值
但，main函数中输出 x、y未局部变量
所以输出局部变量x、y原值
即 3,8
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
#define(宏定义)只是简单的字符串代换，并不在编译过程中进行，而是在预处理过程就已经完成了
typedef是为了增加可读性而为标识符另起的新名称，它具有一定的封装性，它是语言编译过程的一部分，但它并不实际分配内存空间。

所以 #define INT_PTR int* 仅仅是将 int* 换了一个名字
typedef int* int_ptr;	则是将int* 封装至int_ptr
所以使用 INT_PTR a, b;	与 int* a, b; 相同，相当于int* a; int b; 仅仅使 a 定义为整型指针
int_ptr c, d;	则相当于int* c; int* d;		c、d均定义为整型指针
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

