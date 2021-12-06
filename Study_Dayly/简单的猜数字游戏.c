#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
//简单的猜数字游戏
//1.随机生成一个1 - 100 之间的 数字
//2.猜大了 和 猜小了 给提示
//3.一局游戏结束返回菜单界面 （可重复玩）
void	nume()
{
	printf("\n    1 ~ 100 猜数字游戏\n");
	printf("**************************\n");
	printf("**                      **\n");
	printf("**      1.开始游戏      **\n");
	printf("**      0.退出游戏      **\n");
	printf("**                      **\n");
	printf("**************************\n");
}
void game()
{																					//rand 函数 生成一个 随机数（伪随机）
	int ret = rand() % 100 + 1;										//rand 范围 0 ~ rand_MAX  %100 + 1  即为 1 ~ 100 
	int guess = 0;
	while (1)
	{
		printf("请输入一个的数字:>");
		scanf("%d", &guess);
		if (guess < ret)
			printf("猜小了\n");
		else if (guess > ret)
			printf("猜大了\n");
		else
		{
			printf("恭喜你，猜中了！！！\n\n"); 
			break;
		}
	}
}
int main()
{
	nume();
	srand((unsigned int)time(NULL));		//使用rand 函数之前需要 用srand 函数来为伪随机数生成器 设置 起点
		//srand 设置之后 rand 随机生成的值 与 srand函数后的值有关  所以利用不停变化的时间戳 来控制
		//time 可以生成一个 时间戳
	int input = 0;
	do
	{
		printf("请选择序号:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
		{
			printf("\n游戏正在退出");
			Sleep(2000); 
			printf("\n游戏已退出");
			break;
		}
		default:
			printf("选择错误，重新选择\n");
			break;
		}
	} while (input);

	return 0;
}