#define _CRT_SECURE_NO_WARNINGS

#include "mine_function.h"

void menu()
{
	printf("\n****************************\n");
	printf("******     1. play     ******\n");
	printf("******     0. exit     ******\n");
	printf("*****************************\n");
}

void minegame_main()
{
	char mine[ROWS][COLS] = { 0 };				//布置雷的数组
	char show[ROWS][COLS] = { 0 };				//展示雷的数组
	//初始化棋盘													''内的内容 为初始化内容
	InitiBoard(mine, ROWS, COLS,'0');
	InitiBoard(show, ROWS, COLS,'*');
	//打印棋盘
	DisplayBoard(show, ROW, COL);
	//布置雷
	SetMine(mine, ROW, COL);
			//DisplayBoard(mine, ROW, COL);				//此语句 可用于验证游戏逻辑是否正确
	//排除雷
	FindMine(mine,show,ROW,COL);
}

int main()
{
	int input = 0;
	srand((unsigned int)time(NULL));
	do {
		menu();
		printf("\n请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			minegame_main();
			break;
		case 0:
			printf("\n游戏退出成功！\n");
			break;
		default:
			printf("\n选择错误，请重新选择！\n\n");
			break;
		}

	} while (input);

	return 0;
}

