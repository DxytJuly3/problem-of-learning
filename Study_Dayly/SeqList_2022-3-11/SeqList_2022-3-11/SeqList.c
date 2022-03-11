#define _CRT_SECURE_NO_WARNINGS 1

#include "SeqList.h"

int main()
{
	SeqList s;
	SeqListInit(&s);
	SeqListPushBack(&s, 1);
	SeqListPushBack(&s, 2);
	SeqListPushBack(&s, 3);
	SeqListPrint(&s);
	SeqListPushFront(&s, 4);
	SeqListPushFront(&s, 5);
	SeqListPushFront(&s, 6);
	SeqListPushFront(&s, 7);
	SeqListPushFront(&s, 8);
	SeqListPrint(&s);
	SeqListInsert(&s, 5, 7);
	SeqListPrint(&s);

	return 0;
}