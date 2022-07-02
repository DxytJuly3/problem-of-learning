#define _CRT_SECURE_NO_WARNINGS 1

#include "Blog_List.h"

int main()
{
	ListNode *pList = ListInit();
	ListPushFront(pList, 1);
	ListPushFront(pList, 2);
	ListPushFront(pList, 3);
	ListPushFront(pList, 4);
	ListPushFront(pList, 5);
	ListPushFront(pList, 6);
	ListDestroy(pList);
	pList = NULL;

	return 0;
}