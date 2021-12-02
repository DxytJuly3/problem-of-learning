#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 20

typedef struct node BinTNode;		//自定义二又树的结点类型

typedef BinTNode* BinTree;			//定义二又树的指针

int NodeNum, leaf;					//NodeNum为结点数，leaf为叶子数

BinTree CreatBinTree(void);			//基于先序遍历算法创建二又树

void Preorder(BinTree T);			//DLR先序遍历

void Inorde(BinTree T);				//LDR中序遍历

void Postorder(BinTree T);			//LRD后序遍历

int TreeDepth(BinTree T);			//采用后序遍历求二又树的深度、结点数及叶子数的递归算法

void Levelorder(BinTree T);			//利用”先进先出” (FIFO)队列，按层次遍历二叉树

int countleaf(BinTree T);			//数叶子节点个数







