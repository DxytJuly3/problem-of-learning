#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 3
#define COL 3

void mune();													//菜单函数

void InitiBoard(char board[ROW][COL], int row, int col);		//初始化数组的函数

void DisplayBoard(char board[ROW][COL], int row, int col);		//打印棋盘的函数

void PlayerMove(char board[ROW][COL], int row, int col);		//玩家下棋

void ComputerMove(char board[ROW][COL], int row, int col);		//电脑下棋

char IsWin(char board[ROW][COL], int row, int col);				//判断输赢的返回值

int IsFull(char board[ROW][COL], int row, int col);				//判断棋盘 是否满

void game_main();												//游戏本体函数
