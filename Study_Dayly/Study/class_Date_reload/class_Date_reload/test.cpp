#include "class_Date_reload.h"

int main()
{
	
	Date d1(2025, 2, 2);
	Date d2(2022, 1, 1);

	cout << "d1:: ";
	d1.print();
	cout << "d1 + 100:: ";
	(d1 + 100).print();
	cout << endl << "d1:: ";
	d1.print();
	cout << "d1 + (-100):: ";
	(d1 + (-100)).print();
	cout << endl << "d1:: ";
	d1.print();
	cout << "d1 += 100:: ";
	(d1 += 100).print();
	cout << "d1:: ";
	d1.print();

	cout << endl << "d2:: ";
	d2.print();
	cout << "d2 - 100:: ";
	(d2 - 100).print();
	cout << endl << "d2:: ";
	d2.print();
	cout << "d2 - (-100):: ";
	(d2 - (-100)).print();
	cout << endl << "d2:: ";
	d2.print();
	cout << "d2 -= 100:: ";
	(d2 -= 100).print();

	cout << endl << "d1 - d2:: " << (d1 - d2) << endl;

	return 0;
}