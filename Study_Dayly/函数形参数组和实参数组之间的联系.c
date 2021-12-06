#include <stdio.h>
//函数 形参数组 和 实参数组 之间的联系

/*	void swap(int x, int y)											//此函数 条件为整型    填入整型变量的值后  x，y 被赋予填入变量的值
{																				//但 此函数在交换过程中 只改变了 &x，&y 中的值  ，即仅仅交换了  x，y的值
	int z = 0;																//需要交换的 两个整型变量 依旧没有交换位置 所以 a 和 b 不变
	z = x;
	x = y;
	y = z;
}*/				

void swap(int* px, int* py)													//因为 此函数 所需值为整型 指针   所以  填入条件后  
{																							//此函数可以利用指针直接从 地址 改变 指针指向的地址 中变量的值
	int z = 0;
	z = *px;
	*px = *py;
	*py = z;
}
																							//使用 指针 使自定义函数 与 主函数 之间的变量  产生 控制的联系 （铭记）
int main()
{
	int a = 15;
	int b = 30;

	printf("换位前：a = %d，b = %d \n", a, b);
	//swap(a, b);
	swap(&a, &b);
	printf("换位后：a = %d，b = %d \n", a, b);

	return 0;
}