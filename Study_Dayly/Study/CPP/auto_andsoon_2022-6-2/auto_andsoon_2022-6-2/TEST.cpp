#define _CRT_SECURE_NO_WARNINGS 1

#include <iostream>

int main()
{
	int a = 10;
	auto x = a;
	auto& y = a;
	auto* z = &a;

	std::cout << "x的类型::" << typeid(x).name() << std::endl;
	std::cout << "y的类型::" << typeid(y).name() << std::endl;
	std::cout << "z的类型::" << typeid(z).name() << std::endl;

	return 0;
}