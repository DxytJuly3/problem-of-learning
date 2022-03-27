//最简单的函数代码
//研究函数栈帧的创建与销毁

#include <stdio.h>
double add(double a, double b)
{
	double c = 0;
	c = a + b;

	return c;
}

int main()
{
	double a = 20;
	double b = 10;
	double c = add(a, b);

	return 0;
}