#define _CRT_SECURE_NO_WARNINGS
#include "chess_10_8.h"
void mune()
{
	//ѡ��˵�
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
	printf("�����:>\n");
	while (1)
	{
		printf("����������:>");
		scanf("%d %d", &x, &y);
		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (board[x-1][y-1] == ' ')
			{
				board[x-1][y-1] = '*';
				break;
			}
			else
				printf("����ռ�ã����������룡\n");
		}
		else
			printf("�Ƿ����꣬���������룡\n");
	}
}

void ComputerMove(char board[ROW][COL], int row, int col)
{
	printf("������:>\n");
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

//����ֵΪ '*' ���Ӯ
//����ֵΪ '#' ����Ӯ
//����ֵΪ 'Q' ƽ��
//����ֵΪ 'C' ��Ϸ����
char IsWin(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	//�ж� ��
	for (i = 0; i < row; i++)
	{
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][1] != ' ')
			return board[i][1];	
	}
	//�ж� ��
	for (j = 0; j < col; j++)
	{
		if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[1][j] != ' ')
			return board[1][j];
	}
	//�ж� �Խ���
	if(board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
		return board[1][1];
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
		return board[1][1];
	//�ж� ƽ��
	// IsFull ����ֵ Ϊ 1 ������  ƽ��
	//		  ����ֵ Ϊ 0 ����δ��  ��Ϸ����
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
	//��ʼ�� ����
	InitiBoard(board, ROW, COL);
	//��ӡ ����
	DisplayBoard(board, ROW, COL);
	while (1)
	{
		//�������
		PlayerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
		//��������
		ComputerMove(board, ROW, COL);
		DisplayBoard(board, ROW, COL);
		ret = IsWin(board, ROW, COL);
		if (ret != 'C')
			break;
	}
	if (ret == '*')
		printf("���Ӯ�ˣ�\n");
	else if (ret == '#')
		printf("����Ӯ�ˣ�\n");
	else
		printf("ƽ�֣�\n");
	DisplayBoard(board, ROW, COL);
	printf("\n");
}