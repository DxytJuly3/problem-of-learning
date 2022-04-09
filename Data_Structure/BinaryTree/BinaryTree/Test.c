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
//	int a[] = { 1, 5, 2, 67, 78, 23, 67, 43, 6, 2, 6, 3, 34 };
//	//HeapSort(a, 13);
//	for (int i = 0; i < 13; i++)
//	{
//		printf("%d ", a[i]);
//	}
//	printf("\n");
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
	finOrder(root);
	printf("\n");

	printf("LeafSize %d\n", LeafSize(root));
	int SZ = LevelSize(root, 6);
	printf("LevelSize_2 %d", SZ);
	return 0;
}