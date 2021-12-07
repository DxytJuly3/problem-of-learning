#include <stdio.h>
//计算整数的二进制位有多少 1 
int count_one(int n)
{
	int count = 0;
	while (n)
	{
		count++;
		n = n & (n - 1);
	}

	return count;
}

int main()
{
	int n = 0;
	scanf("%d", &n);
	int count = count_one(n);
	printf("%d", count);

	return 0;
}