#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>

int main()
{
	int a = 10;
	auto x = a;
	auto& y = a;
	auto* z = &a;

	std::cout << "x������::" << typeid(x).name() << std::endl;
	std::cout << "y������::" << typeid(y).name() << std::endl;
	std::cout << "z������::" << typeid(z).name() << std::endl;

	return 0;
}