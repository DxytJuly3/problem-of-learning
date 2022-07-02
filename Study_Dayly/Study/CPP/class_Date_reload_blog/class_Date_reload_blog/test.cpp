#include "class_Date_reload_blog.h"

void Datetest1()
{
	Date d1(2022, 1, 1);
	Date d2(2022, 2, 2);

	if (d1 > d2)
	{
		cout << "d1 > d2" << endl;
	}
	else
	{
		cout << "d1 <= d2" << endl;
	}
}

void Datetest2()
{
	Date d1(1970, 1, 1);
	Date d2(2022, 2, 2);
	Date d3(2000);
	Date d4;

	d4 = d3 = d2 = d1;
	d2.print();
	d3.print();
	d4.print();
}

void Datetest3()
{
	Date d1(1970, 1, 1);
	Date d2 = d1;

	d2 = d1;
}

void Datetest4()
{
	Date d1(1970, 1, 1);
	Date d2 = d1;

	d2 = d1;
	if (d2 == d1)
	{
		cout << "d2 == d1" << endl;
	}
	else
	{
		d2.print();
		d1.print();
	}
}

void Datetest5()
{
	Date d1(2022, 1, 1);
	Date d2;
	d2 = d1 + 50;
	d1.print();
	d2.print();
}

void Datetest6()
{
	Date d1(2022, 1, 1);
	d1 += 50;
	d1.print();
}

void Datetest7()
{
	Date d1(2022, 1, 1);
	Date d2 = d1 - 50;
	Date d3 = d1 - 1;
	d1.print();
	d2.print();
	d3.print();
}

void Datetest8()
{
	Date d1(2022, 1, 1);
	Date d2 = (d1 -= 1);
	d1.print();
	d2.print();
}

void Datetest9()
{
	Date d1(2022, 1, 1);
	Date d2(2000, 5, 4);
	
	cout << "d1 - d2:: " << (d1 - d2) << endl;
	cout << "d2 - d1:: " << (d2 - d1) << endl;
}

void test(Date a)
{
	a.print();
}
int main()
{
	const Date i;
	test(i);

	return 0;
}