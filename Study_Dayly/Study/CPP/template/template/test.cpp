#include "template.h"

void test1()
{
	int a = 1, b = 2;
	double c = 3.3, d = 6.6;

	swap(a, b);
	swap(c, d);
	cout << "a::" << a << "  b::" << b << endl;
	cout << "c::" << c << "  d::" << d << endl;
}

void test2()
{
	int a = 10, b = 20;
	double c = 3.3, d = 6.6;

	swap<int>(a, b);
	swap<double>(c, d);
	cout << "a::" << a << "  b::" << b << endl;
	cout << "c::" << c << "  d::" << d << endl;
}

//void test3()
//{
//	int a = 1;
//	double c = 3.3;
//
//	int b = add(a, (int)c);
//	double d = add<double>(a, c);
//	cout << b << endl;
//	cout << d << endl;
//}

void test4()
{
	int a = 1, b = 2;
	double c = 3.3, d = 6.6;

	double sumb = add(a, c);
	int sumi = add(d, b);
}


int main()
{
	SeqList<int> slt;

	return 0;
}