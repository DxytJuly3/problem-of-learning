#define _CRT_SECURE_NO_WARNINGS

#include "chess_10_8.h"

int main()
{
	int input = 0;
	//随机值前的调用
	srand((unsigned int)time(NULL));
	do
	{
		mune();
		printf("请选择序号:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			//游戏本体函数
			game_main();
			break;
		case 0:
		printf("退出成功！");
			break;
		default:
			printf("选择错误，请重新选择！\n");
			break;
		}
	} while(input);

	return 0;
}
