#include <stdio.h>
//喝汽水问题
//喝汽水，1瓶汽水1元，2个空瓶可以换一瓶汽水，给n元，可以多少汽水
int drink_num(int money)
{
	if (money % 2 == 0)
		return money + drink_num(money / 2);
	else if (money % 2 == 1 && money != 1)
		return money + drink_num(money / 2) + 1;
	else
		return money;
}

int main()
{
	int money = 0;
	scanf("%d", &money);
	int num = drink_num(money);
	printf("%d\n", num);

	return 0;
}