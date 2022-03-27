#define _CRT_SECURE_NO_WARNINGS 1

#include "List.h"

void Test1()
{
	ListNode* phead = ListInit();
	printf("头插 1 、2 、3 、4 测试:>\n");
	ListPushFront(phead, 1);
	ListPushFront(phead, 2);
	ListPushFront(phead, 3);
	ListPushFront(phead, 4);
	ListPrint(phead);
	printf("尾插 5 、6 、7 、8 测试:>\n");
	ListPushBack(phead, 5);
	ListPushBack(phead, 6);
	ListPushBack(phead, 7);
	ListPushBack(phead, 8);
	ListPrint(phead);
	printf("尾删测试 * 2\n");
	ListPopBack(phead);
	ListPopBack(phead);
	ListPrint(phead);
	printf("头删测试 * 2\n");
	ListPopFront(phead);
	ListPopFront(phead);
	ListPrint(phead);
	printf("查找测试：9\n");
	ListNode* FindNode1 = ListFind(phead, 9);
	printf("FindNode1 = %p\n", FindNode1);
	printf("查找测试：1\n");
	ListNode* FindNode2 = ListFind(phead, 1);
	printf("FindNode2 = %p\n", FindNode2);

	printf("FindNode2 位置(1 所在位置)前插入 10:>\n");
	ListInsert(FindNode2, 10);
	ListPrint(phead);
	printf("删除 FindNode2 位置(1 所在位置) 节点:>\n");
	ListErase(FindNode2);
	ListPrint(phead);
	printf("销毁链表:>\n");
	printf("销毁前 phead 地址:%p\n", phead);
	ListDestroy(&phead);
	printf("销毁后 phead 地址:%p\n", phead);
}

int main()
{
	Test1();

	return 0;
}