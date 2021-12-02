#define _CRT_SECURE_NO_WARNINGS

#include "mine_function.h"

void InitiBoard(char mine[ROWS][COLS], int row, int col, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			mine[i][j] = set;					//将数组个元素 初始化为 set 中的字符
		}
	}
}

void DisplayBoard(char mine[ROWS][COLS], int row, int col)			//打印雷盘
{
	int i = 0;
	int j = 0;
	printf("\n-------------扫雷游戏-------------\n\n");
	for (i = 0; i <= row; i++)
	{
		printf(" %d ", i);
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf(" %d ", i);
		for (j = 1; j <= col; j++)
		{
			printf(" %c ", mine[i][j]);
		}
		printf("\n");
	}
}

void SetMine(char mine[ROWS][COLS], int row, int col)			//随机 在棋盘中 布置雷
{
	int count = MINE_NUM;
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (mine[x][y] == '0')
		{
			mine[x][y] = '1';
			count--;
		}
	}
}

//static 修饰函数 ，改变函数作用范围  使函数仅能在本 .c文件使用  且不影响其他文件中同函数名的函数
static int MineNum(char mine[ROWS][COLS], int x, int y)
{
	return	mine[x - 1][y - 1] +
		mine[x - 1][y] +
		mine[x - 1][y + 1] +
		mine[x][y - 1] +
		mine[x][y + 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x + 1][y + 1] - 8 * '0';
	//判断 mine[x][y] 周围是否有雷   数组中 字符1 为雷 字符0 为空	和 - 8个字符0 即为雷个数
}

void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
	int count = 0;
	while (1)
	{
		printf("\n请输入坐标:>");
		scanf("%d%d", &x, &y);		//x和y 的 合法范围 是 1 - col/row
		//判断坐标的合法性
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (mine[x][y] == '1')
			{
				printf("\n你被炸死了！透透的！\n\n");
				DisplayBoard(show, ROW, COL);
				break;
			}
			else
			{
				int count_mine = MineNum(mine, x, y);
				show[x][y] = count_mine + '0';
				DisplayBoard(show, ROW, COL);
				count++;								//排雷次数总和
				if (count == row * col - MINE_NUM)			//因一次只能排除一个 则排雷次数 最多时 过关
				{
					printf("\n恭喜过关！\n\n");
					break;
				}
			}
		}
		else
		{
			printf("\n坐标非法，请重新输入\n\n");
		}
	}
}
