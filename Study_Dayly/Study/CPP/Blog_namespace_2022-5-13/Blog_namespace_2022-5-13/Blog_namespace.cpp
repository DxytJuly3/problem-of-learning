#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>

namespace July
{
	int J = 10;
	int U = 11;
	namespace July1
	{
		int L = 20;
		int Y = 21;
	}
}

using namespace July;

int main()
{
	printf("%d\n", J);
	printf("%d\n", July1::L);

	return 0;
}