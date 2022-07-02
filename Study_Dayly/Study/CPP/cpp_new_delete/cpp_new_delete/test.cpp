#include "cpp_new_delete.h"

void test()
{
	// 申请单个Test类型的对象
	Test* p1 = new Test;
	delete p1;

	cout << endl << endl;

	// 申请10个Test类型的对象
	Test* p2 = new Test[10];
	delete[] p2;
}

void test1()
{
	SeqList* slt = new SeqList;
	delete slt;

	SeqList* slt1 = (SeqList*)malloc(sizeof(SeqList));
}

void test2()
{
	SeqList* slt = (SeqList*)operator new(sizeof(SeqList));

	new(slt)SeqList;
}
int main()
{
	char* pc = new char[100];
	delete pc;

	return 0;
}