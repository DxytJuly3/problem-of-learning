#include <stdio.h>
//输入n个成绩，换行输出n个成绩中最高分数和最低分数的差。
int main()
{
	int n = 0;
	int max = 0;
	int min = 10000;
	int num = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &num);
		if (max < num)
			max = num;
		if (min > num)
			min = num;
	}
	printf("%d", max - min);

	return 0;
}

