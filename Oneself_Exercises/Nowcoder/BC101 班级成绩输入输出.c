#include <stdio.h>
//输入一个班级5个学生各5科成绩，输出5个学生各5科成绩及总分。
int main()
{
	double score[5][6] = { 0 };
	int i = 0;
	int j = 0;
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
			scanf("%lf", &score[i][j]);
	}
	for (i = 0; i < 5; i++)
	{
		double sum = 0;
		for (j = 0; j < 5; j++)
		{
			sum += score[i][j];
		}
		score[i][5] = sum;
	}
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 6; j++)
		{
			printf("%.1lf ", score[i][j]);
		}
		printf("\n");
	}

	return 0;
}