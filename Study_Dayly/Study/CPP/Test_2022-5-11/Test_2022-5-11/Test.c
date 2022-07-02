#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>

void f(int a)
{
	printf("int");
}

int main()
{
	f(NULL);

	return 0;
}