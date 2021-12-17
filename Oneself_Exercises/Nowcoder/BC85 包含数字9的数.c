#include <stdio.h>
//今年是2019年，KiKi想知道1~2019中有多少个包含数字9的数。包含数字的数是指有某一位是“9”的数，例如“2019”、“199”等。
int main()
{
	int i = 0;
	int flag = 0;
	for (i = 0; i < 2020; i++)
	{
		int set = i;
		while (set)
		{
			if(set % 10 != 9)
				set /= 10;
			else
			{
				flag++;
				break;
			}
		}
	}
	printf("%d ", flag);

	return 0;
}