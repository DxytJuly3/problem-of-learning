#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define ROW 9	
#define COL 9					//游戏中横纵棋盘排列数

#define ROWS ROW+2				
#define COLS COL+2				//游戏中为方便四边所在方格的周围 排雷  需各向外扩展一行、列

#define MINE_NUM 10				//游戏中  雷的个数

//初始化棋盘 函数
void InitiBoard(char mine[ROWS][COLS], int row, int col, char set);			
//打印棋盘 函数
void DisplayBoard(char mine[ROWS][COLS], int row, int col);
//布置雷 函数
void SetMine(char mine[ROWS][COLS], int row, int col);
//排除雷 函数
void FindMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col);