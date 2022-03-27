#include <stdio.h>
//整数的二进制位 奇、偶数位输出
int main()
{
	int n = 0;
	int x = 0;
	int i = 0;
	scanf("%d", &n);
	for (i = 0; i < 32; i += 2)
	{//输出 奇数位
		x = (n >> i) & 1;
		printf("%d", x);
	}
	printf("\n");
	for (i = 1; i < 32; i += 2)
	{//输出 偶数位
		x = (n >> i) & 1;
		printf("%d", x);
	}
	
	return 0;
}