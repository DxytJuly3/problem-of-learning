#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max 20

typedef struct node BinTNode;		//�Զ���������Ľ������

typedef BinTNode* BinTree;			//�����������ָ��

int NodeNum, leaf;					//NodeNumΪ�������leafΪҶ����

BinTree CreatBinTree(void);			//������������㷨����������

void Preorder(BinTree T);			//DLR�������

void Inorde(BinTree T);				//LDR�������

void Postorder(BinTree T);			//LRD�������

int TreeDepth(BinTree T);			//���ú�����������������ȡ��������Ҷ�����ĵݹ��㷨

void Levelorder(BinTree T);			//���á��Ƚ��ȳ��� (FIFO)���У�����α���������

int countleaf(BinTree T);			//��Ҷ�ӽڵ����







