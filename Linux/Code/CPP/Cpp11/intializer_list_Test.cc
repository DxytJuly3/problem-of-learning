#include <iostream>
//
//int main() {
//	auto li = { 1, 2, 3, 4, 5 };
//	std::cout << typeid(li).name() << std::endl;
//
//	return 0;
//}

//int main() {
//    int b = 1;
//    auto c = 3.3;
//    std::cout << typeid(b).name() << std::endl;
//	std::cout << typeid(c).name() << std::endl;
//    
//    return 0;
///}

int main() {
    decltype(1 * 1) d;
    decltype(2 * 2.2) e;
	std::cout << typeid(d).name() << std::endl;
	std::cout << typeid(e).name() << std::endl;
    
    return 0;
}
