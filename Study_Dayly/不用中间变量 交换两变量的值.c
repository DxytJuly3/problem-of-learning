#include <stdio.h>
//不用中间变量 交换两变量的值
int main()
{
	int a = 0;
	int b = 0;
	scanf("%d%d", &a, &b);
	printf("交换前:>");
	printf(" a = %d,b = %d\n", a, b);		
	a = a ^ b;		// 异或 a = a ^ b;		相同为 0，相异为 1		所以 b ^ b  ==  0		b ^ 0  ==  b
	b = a ^ b;		// b = a ^ b ^ b	==	  a（原来的）		a ^ b ^ b  ==  a ^ 0  ==  a
	a = a ^ b;		// a = a ^ b ^ a	==	  b（原来的）		a ^ b ^ a  ==  0 ^ b  ==  b
	printf("交换后:>");
	printf(" a = %d,b = %d", a, b);

	return 0;
}