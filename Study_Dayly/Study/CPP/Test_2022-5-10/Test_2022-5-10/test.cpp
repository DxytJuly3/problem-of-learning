#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>
using namespace std;

int main()
{
	int c = 0;
	int a = 100;
	int& b = a;
	b = c;

	return 0;
}