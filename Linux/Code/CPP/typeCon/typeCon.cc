#include <cstdlib>
#include <iostream>
#include <ostream>

int main() {
	double d = 123.12398;
	int a = static_cast<int>(d);
	std::cout << d << " : " << a << std::endl;

	return 0;
}
//int main() {
//	int* a = (int*)std::malloc(sizeof(int));
//	*a = 20;
//
//	std::cout << *a << std::endl;
//
//	std::free(a);
//
//	return 0;
//}
//int main() {
//	char a = 'c';
//	int b = a;
//	std::cout << a << " : " << b << std::endl;
//
//	//int* c= a;
//
//	return 0;
//}
////int main() {
//	size_t pos = 0;
//	int i = 10;
//	while (i >= pos) {
//		i--;
//		std::cout << i << std::endl;
//	}
//
//	return 0;
//}
