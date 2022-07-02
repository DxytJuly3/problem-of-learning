#include "class_Date_reload.h"

int main()
{
	
	Date d1(2025, 2, 2);
	Date d2(2022, 1, 1);

	d2 -= 1;
	d2.print();

	return 0;
}