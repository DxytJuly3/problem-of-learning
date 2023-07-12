#include <cstdio>
#include <iostream>
#include <ostream>

//class Singleton {
//public:
//	static Singleton* getInstance() {
//		return &_instance;
//	}
//
//private:
//	Singleton() {}
//
//	Singleton(const Singleton&) = delete;
//	Singleton& operator=(const Singleton&) = delete;
//
//	static Singleton _instance; // 声明
//};
//// 定义
//Singleton Singleton::_instance;

class Singleton {
public:
	static Singleton* getInstance() {
		if (_instance == nullptr) {
			_instance = new Singleton();
		}

		return _instance;
	}
	class CGarbo {
	public:
		~CGarbo() {
			if (_instance)
				delete _instance;
		}
	};

	// 定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数从而释放单例对象
	static CGarbo Garbo;

private:
	Singleton() {}

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

	static Singleton* _instance; // 声明
};
// 定义
Singleton* Singleton::_instance = nullptr;

void func1() {
	std::cout << "func1" << std::endl;

	Singleton* singleT4 = Singleton::getInstance();
	Singleton* singleT5 = Singleton::getInstance();

	std::cout << singleT4 << std::endl;
	std::cout << singleT5 << std::endl;
}

int main() {
	Singleton* singleT1 = Singleton::getInstance();
	Singleton* singleT2 = Singleton::getInstance();
	Singleton* singleT3 = Singleton::getInstance();

	std::cout << singleT1 << std::endl;
	std::cout << singleT2 << std::endl;
	std::cout << singleT3 << std::endl;

	func1();

	return 0;
}
