#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 3
#define COL 3

void mune();													//�˵�����

void InitiBoard(char board[ROW][COL], int row, int col);		//��ʼ������ĺ���

void DisplayBoard(char board[ROW][COL], int row, int col);		//��ӡ���̵ĺ���

void PlayerMove(char board[ROW][COL], int row, int col);		//�������

void ComputerMove(char board[ROW][COL], int row, int col);		//��������

char IsWin(char board[ROW][COL], int row, int col);				//�ж���Ӯ�ķ���ֵ

int IsFull(char board[ROW][COL], int row, int col);				//�ж����� �Ƿ���

void game_main();												//��Ϸ���庯��
