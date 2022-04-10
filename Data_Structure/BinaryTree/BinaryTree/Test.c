#define _CRT_SECURE_NO_WARNINGS 1

//#include "Heap.h"
//
//int main()
//{
//	//Heap hp;
//	//HeapInit(&hp);
//	//HeapPush(&hp, 5);
//	//HeapPush(&hp, 9);
//	//HeapPush(&hp, 2);
//	//HeapPush(&hp, 6);
//	//HeapPush(&hp, 9);
//	//HeapPush(&hp, 1);
//	//HeapPush(&hp, 7);
//	//HeapPush(&hp, 4);
//	//HeapPush(&hp, 3);
//	//HeapPrint(&hp);
//	//printf("\n");
//
//	//HeapPop(&hp);
//	//HeapPrint(&hp);
//	//printf("\n");
//
//	//HeapPop(&hp);
//	//HeapPrint(&hp);
//	//printf("\n");
//
//	//HeapPop(&hp);
//	//HeapPrint(&hp);
//	//printf("\n");
//
//	 // HeapSort 验证
//	/*int a[] = { 5, 2, 67, 78, 23, 67, 43, 6, 2, 6, 3, 22, 33};
//	HeapSort(a, 13);
//	for (int i = 0; i < 13; i++)
//	{
//		printf("%d ", a[i]);
//	}
//	printf("\n");*/
//
//	// Top-K 问题
//	// 海量数据，取前几名  数据量可能  百亿 千亿 万亿
//
//	// 不可能采用常规遍历 等方法去求前几   因为常规遍历需要将数据存入内存中，海量的数据对于内存来说压力过大
//	// 所以海量的数据一般是存在文件中的，但是文件只能顺序读取，不能随机读取	
//	// 所以如果按照常规的遍历求最大  次大  第三大 这种方法，海量的数据遍历 k 次，会非常的麻烦
//	// 求前 20 就得遍历 20次，求前 50 就得遍历 50次
//	// Top-K 算法就是为处理这样的问题 写出来的
//	// 如果求 海量数据中的前 K 个最大的
//	// 就将文件中前 K个位置的数据 建立为 K 个节点的小根堆，然后再从 K 位置依次向后遍历 与 小根堆的根 作比较 比根大 就入堆 并向下调整
//	// 这样从头到尾遍历一遍 就保证了 有K个节点的小根堆 中的数据，就是海量数据中的 前 K 个最大的数据
//	// 如果求 海量数据中的前 K 个最小的，按照相同的思路建立 大根堆就是了
//
//	// 以 求前 10 个最大的数据为例（模拟）
//	//int n = 10000;
//	//int* a = (int*)malloc(sizeof(int)*n);
//	//srand(time(0));
//	//for (size_t i = 0; i < n; ++i)
//	//{//	在 数组a 中存放 小于 1000000 的随机值
//	//	a[i] = rand() % 1000000;
//	//}
//	//// 在随机存放 10 个比 1000000 大的值
//	//a[5] = 1000000 + 1;
//	//a[1231] = 1000000 + 2;
//	//a[531] = 1000000 + 3;
//	//a[5121] = 1000000 + 4;
//	//a[115] = 1000000 + 5;
//	//a[2305] = 1000000 + 6;
//	//a[99] = 1000000 + 7;
//	//a[76] = 1000000 + 8;
//	//a[423] = 1000000 + 9;
//	//a[0] = 1000000 + 1000;
//	//// Top-K 求解 （模拟）
//	//PrintTopK(a, n, 10);
//
//	return 0;
//}

#include "BinaryTree.h"

int main()
{
	BTNode* root = creatBinaryTree();

	printf("先序遍历:> ");
	prevOrder(root);
	printf("\n");

	printf("中序遍历:> ");
	inOrder(root);
	printf("\n");

	printf("后序遍历:> ");
	postOrder(root);
	printf("\n");

	// 测试计算 二叉树节点数量 （全局遍历计数）
	// 如果使用全局变量计数，每次调用此函数前 就需要将全局变量置零
	/*NodeCount = 0;
	BTNodeSize(root);
	printf("NodeSize:> %d\n", NodeCount);*/

	// 测试计算 二叉树节点数量 （分治思想）
	printf("BTNodeSize:> %d\n", BTNodeSize(root));

	// 测试计算 叶子结点的数量
	printf("LeafSize:> %d\n", LeafSize(root));
	// 测试计算 第n层的节点数量 （当n超出树的深度）
	printf("LevelSize_6:> %d\n", LevelSize(root, 6));
	// 测试计算 第n层的节点数量 （当n未超出树的深度）
	printf("LevelSize_2:> %d\n", LevelSize(root, 2));
	// 测试计算 二叉树的深度
	printf("Depth:> %d\n", BinaryTreeDepth(root));

	return 0;
}