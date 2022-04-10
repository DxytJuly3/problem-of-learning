#define _CRT_SECURE_NO_WARNINGS 1

#include "BinaryTree.h"

BTNode* buyBTNode(BTDataType x)
{
	BTNode* newNode = (BTNode*)malloc(sizeof(BTNode));
	if (newNode == NULL)
	{
		printf("malloc failed\n");
		exit(-1);
	}

	newNode->left = newNode->right = NULL;
	newNode->data = x;

	return newNode;
}

BTNode* creatBinaryTree()
{
	BTNode* node1 = buyBTNode(1);
	BTNode* node2 = buyBTNode(2);
	BTNode* node3 = buyBTNode(3);
	BTNode* node4 = buyBTNode(4);
	BTNode* node5 = buyBTNode(5);
	BTNode* node6 = buyBTNode(6);

	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;

	return node1;
}

void prevOrder(BTNode* root)
{// 递归 先序遍历
	if (root == NULL)	// 当根未空，即二叉树不存在
	{
		printf("NULL ");
		return;
	}
	
	// 先序遍历访问顺序：根、左孩子、右孩子
	printf("%d ", root->data);
	prevOrder(root->left);
	prevOrder(root->right);
}

void inOrder(BTNode* root)
{// 递归 中序遍历
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}

	// 中序遍历访问顺序：左孩子、根、右孩子
	// 即如果存在左孩子，就一直去到左孩子节点
	// 直到左孩子为空，访问空，然后访问 根
	inOrder(root->left);
	printf("%d ", root->data);
	inOrder(root->right);
}

void postOrder(BTNode* root)
{
	if (root == NULL)
	{
		printf("NULL ");
		return;
	}

	postOrder(root->left);
	postOrder(root->right);
	printf("%d ", root->data);
}


// 二叉树节点数量 （全局变量计数的方法）
//NodeCount = 0;
//void BTNodeSize(BTNode* root)
//{
//	if (root == NULL)
//		return 0;
//
//	NodeCount++;
//	BTNodeSize(root->left);
//	BTNodeSize(root->right);
//}


// 二叉树节点数量（分治思想）
int BTNodeSize(BTNode* root)
{
	// 当前节点为空就返回 0，表示不加 1
	// 当前节点不为空，就 + 1，并且进入下一个孩子
	return root == NULL ? 0 : BTNodeSize(root->left) + BTNodeSize(root->right) + 1;
}

// 叶子节点数量（分治思想）
int LeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;

	// 左右孩子都为空 返回1
	// 因为递归层层递进
	// 所以 最后返回的是 从根的左孩子向下的所有叶子节点的数量 + 从根的右孩子向下所有叶子结点的数量
	return (root->left == NULL && root->right == NULL) ? 1 : LeafSize(root->left) + LeafSize(root->right);
}

int LevelSize(BTNode* root, int k)
{
	if (root == NULL || (root->left == NULL && root->right == NULL))
		return 0;

	return k == 1 ? 1 : LevelSize(root->left, k - 1) + LevelSize(root->right, k - 1);
}

int BinaryTreeDepth(BTNode* root)
{
	if (root == NULL)
		return 0;

	//return (root->left == NULL && root->right == NULL) ? 1 : (BinaryTreeDepth(root->left) > BinaryTreeDepth(root->right) ? (BinaryTreeDepth(root->left) + 1) : (BinaryTreeDepth(root->right) + 1));
	int leftDepth = BinaryTreeDepth(root->left);
	int rightDepth = BinaryTreeDepth(root->right);

	return leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
}

// 层序遍历
void levelOrder(BTNode* root)
{

}

// 判断二叉树是否是完全二叉树
bool BTComplete(BTNode* root)
{

}