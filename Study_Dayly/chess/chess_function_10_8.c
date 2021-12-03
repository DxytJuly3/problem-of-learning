#define _CRT_SECURE_NO_WARNINGS
#include "chess_10_8.h"
void mune()
{
	//选择菜单
	printf("*********************************\n");
	printf("********     1. play     ********\n");
	printf("********     0. exit     ********\n");
	printf("*********************************\n");
}

void InitiBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			board[i][j] = ' ';
		}
	}
}

void DisplayBoard(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			if (j < col - 1)
				printf("|");
		}
		printf("\n");
		if (i < row - 1)
		{
			int j = 0;
			for (j = 0; j < col; j++)
			{
				printf("---");
				if (j < col - 1)
					printf("|");
			}
			printf("\n");
		}
	}
}

void PlayerMove(char board[ROW][COL], int row, int col)
{
	int x = 0;
	int y = 0;
	printf("玩家走:>\n");
	while (1)
	{
		printf("请输入坐标:>");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (board[x-1][y-1] == ' ')
			{
				board[x-1][y-1] = '*';
				break;
			}
			else
				printf("坐标占用，请重新输入！\n");
		}
		else
			printf("非法坐标，请重新输入！\n");
	}
}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	printf("电脑走:>\n");
	while (1)
	{
		int x = rand() % row;
		int y = rand() % col;
		if (board[x][y] == ' ')
		{
			board[x][y] = '#';
			break;
		}
	}
}

int IsFull(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (board[i][j] == ' ')
			{
				return 0;
				break;
			}
		}
	}
	return 1;
}

//返回值为 '*' 玩家赢
//返回值为 '#' 电脑赢
//返回值为 'Q' 平局
//返回值为 'C' 游戏继续
char IsWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	//判断 行
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
			return board[i][1];	
	}
	//判断 列
	for (j = 0; j < col; j++)
	{
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ')
			return board[1][j];
	}
	//判断 对角线
	if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
		return board[1][1];
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
		return board[1][1];
	//判断 平局
	// IsFull 返回值 为 1 棋盘满  平局
	//		  返回值 为 0 期盼未满  游戏继续
	int ret = IsFull(board, row, col);
	if (ret == 1)
		return 'Q';

	return 'C';
}

void game_main()
{
	int j = 0;
	int i = 0;
	char ret;
	char board[ROW][COL];
	//初始化 数组
	InitiBoard(board, ROW, COL);
	//打印 棋盘
	DisplayBoard(board, ROW, COL);
	while (1)
	{
		//玩家下棋
		PlayerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
		//电脑下棋
		ComputerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
	}
	if (ret == '*')
		printf("玩家赢了！\n");
	else if (ret == '#')
		printf("电脑赢了！\n");
	else
		printf("平局！\n");
	DisplayBoard(board, ROW, COL);
	printf("\n");
}