#pragma once 

//int NodeCount = 0;

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>


typedef int BTDataType;

// 链式二叉树
// 链式二叉树 需要理解一个重要的思想：
// 每一棵树，都可以分为 根、左孩子、右孩子
// 即 存在一棵二叉树：		 1
//					  2     3
//			        4   5 6   5
// 则可以看作   1 为根， 2 为左孩子， 3 为右孩子
// 同样可以看作 2 为根， 4 为左孩子， 5 为右孩子

// 如果没有左孩子 或者 没有右孩子 那么左孩子 = 右孩子 = NULL
// 即         4 为根， 4的左孩子为 NULL， 4的右孩子为 NULL
typedef struct BinaryTreeNode
{
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
	BTDataType data;
}BTNode;

// 创建新节点
BTNode* buyBTNode(BTDataType x);
// 创建新的二叉树的函数（固定的）
BTNode* creatBinaryTree();

// 先序遍历
void prevOrder(BTNode* pbt);
// 中序遍历
void inOrder(BTNode* pbt);
// 后序遍历
void postOrder(BTNode* root);
// 二叉树节点的个数
int BTNodeSize(BTNode* root);
// 二叉树叶子节点数量
int LeafSize(BTNode* root);
// 第K层 节点数量
int LevelSize(BTNode* root, int k);
// 二叉树深度
int BinaryTreeDepth(BTNode* root);
// 层序遍历
void BinaryTreeLevelOrder(BTNode* root);
// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root);
