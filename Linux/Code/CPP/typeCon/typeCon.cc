#include <iostream>
#include <cstdlib>
#include <ostream>

using std::cout;
using std::endl;

class A {};

class B : public A {};
//class A {
//public:
//	virtual void f() {}
//	virtual bool isPoly() {
//		return false;
//	}
//};
//
//class B : public A {
//public:
//	virtual bool isPoly() {
//		return true;
//	}
//};

void fun(A* pa) {
//	if(pa->isPoly()) {
//		cout << "多态调用, 指向子类对象" << endl;
//	}
//	else if(!pa->isPoly()) {
//		cout << "指向父类对象" << endl;
//	}
	B* pb1 = static_cast<B*>(pa);
	B* pb2 = dynamic_cast<B*>(pa);

	cout << "pb1:" << pb1 << endl;
	cout << "pb2:" << pb2 << endl;
}

int main() {
	A a;
	B b;
	fun(&a);
	fun(&b);

	return 0;
}

//int main() {
//	A a;
//	B b;
//	B* pb = &a;
//
//	return 0;
//}

//int main() {
//	volatile const int val = 100;
//	int* pV = const_cast<int*>(&val);
//	*pV = 200;
//
//	std::cout << val << std::endl;
//	std::cout << *pV << std::endl;
//
//	return 0;
//}

//int main(){
//	const int val = 100;
//	int* pV = (int*)&val;
//	*pV = 200;
//
//	std::cout << val << std::endl;
//	std::cout << *pV << std::endl;
//
//	return 0;
//}
//int main() {
//	double d = 123.12398;
//	int a = static_cast<int>(d);
//	std::cout << d << " : " << a << std::endl;
//
//	// 报错
//	//int* c = static_cast<int*>(a);
//	int* b = &a;
//	int* c = reinterpret_cast<int*>(a);
//	int e = reinterpret_cast<int>(b);
//	std::cout << c << std::endl;
//	std::cout << b << std::endl;
//
//	return 0;
//}
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
