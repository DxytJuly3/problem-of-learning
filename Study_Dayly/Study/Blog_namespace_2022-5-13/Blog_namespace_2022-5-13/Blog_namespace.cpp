#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>

namespace July
{
	int J = 10;
	int U = 11;
	namespace July1
	{
		int J = 10;
		int U = 11;
		namespace July11
		{
			int J = 10;
			int U = 11;
		}
	}
}

namespace July_
{
	int J = 20;
	int U = 21;
}

int J = 30;
int U = 31;

int main()
{

	return 0;
}