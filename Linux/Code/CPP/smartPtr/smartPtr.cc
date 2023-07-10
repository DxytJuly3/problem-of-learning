#include <cstdio>
#include <iostream>
#include <memory>
#include <exception>
#include <ostream>

using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::invalid_argument;

namespace July {
	template <class T>
	class auto_ptr {
	public:
		auto_ptr(T* ptr = nullptr)
			: _ptr(ptr) {}

		auto_ptr(auto_ptr<T>& ap)
			: _ptr(ap._ptr) {
			ap._ptr = nullptr;
		}

		auto_ptr<T>& operator=(auto_ptr<T>& ap) {
			// 防止自我赋值
			if (this != &ap) {
				// 先清除被赋值对象中的资源
				if (_ptr)
					delete _ptr;

				_ptr = ap._ptr;
				ap._ptr = nullptr;
			}
		}

		T& operator*() {
			return *_ptr;
		}

		T* operator->() {
			return _ptr;
		}

		~auto_ptr() {
			if (_ptr) {
				cout << "析构 释放资源" << _ptr << endl;
				delete _ptr;
				_ptr = nullptr;
			}
		}

	private:
		T* _ptr;
	};

	template <class T>
	class unique_ptr {
	public:
		// RAII思想
		unique_ptr(T* ptr = nullptr)
			: _ptr(ptr) {}

		~unique_ptr() {
			if (_ptr) {
				cout << "delete" << _ptr << endl;
				delete _ptr;
				_ptr = nullptr;
			}
		}

		T& operator*() {
			return *_ptr;
		}

		T* operator->() {
			return _ptr;
		}

		// C++11 之后
		unique_ptr(const unique_ptr<T>& up) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>& up) = delete;

	private:
		// C++98 可以这样实现
		// 1. 只声明不实现, 不过如果是public, 这种方法可以在其他地方实现功能
		// 2. 声明成私有
		//	unique_ptr(const unique_ptr<T>& sp);
		//	unique_ptr<T>& operator=(const unique_ptr<T>& sp);
		T* _ptr;
	};

	template <class T>
	class shared_ptr {
	public:
		// RAII思想
		shared_ptr(T* ptr)
			: _ptr(ptr)
			, _pCount(new int(1)) {}

		~shared_ptr() {
			release();
		}

		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount) {
			(*_pCount)++;
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp) {
			// 这里需要用 维护资源是否相同来判断 是否需要执行赋值操作
			// 不能只判断对象是否相同, 因为不同对象维护的资源也可能相同
			if (_ptr != sp._ptr) {
				release();

				_ptr = sp._ptr;
				_pCount = sp._pCount;
				++(*_pCount);
			}
			else {
				// 为了演示
				cout << "自我赋值, 跳过执行" << endl;
			}

			return *this;
		}

		T& operator*() {
			return *_ptr;
		}

		T* operator->() {
			return _ptr;
		}

		// 释放资源函数
		// 当前对象的引用计数为1时, 进行资源释放操作
		void release() {
			if (--(*_pCount) == 0 && _ptr) {
				cout << "delete" << _ptr << endl;
				delete _ptr;
				_ptr = nullptr;

				delete _pCount;
				_pCount = nullptr;
			}
		}

		T* get() const {
			return _ptr;
		}

		int getCount() {
			return *_pCount;
		}

	private:
		T* _ptr;
		int* _pCount;
	};

	// 简化版本的weak_ptr实现
	template <class T>
	class weak_ptr {
	public:
		weak_ptr()
			: _ptr(nullptr) {}

		weak_ptr(const shared_ptr<T>& sp)
			: _ptr(sp.get()) {}

		weak_ptr<T>& operator=(const shared_ptr<T>& sp) {
			_ptr = sp.get();
			return *this;
		}

		T& operator*() {
			return *_ptr;
		}

		T* operator->() {
			return _ptr;
		}

	private:
		T* _ptr;
	};
} // namespace July

template <class T>
class SmartPtr {
public:
	SmartPtr(T* ptr = nullptr)
		: _ptr(ptr) {}

	SmartPtr(const SmartPtr<T>& sp)
		: _ptr(sp._ptr) {}

	SmartPtr<T>& operator=(const SmartPtr<T>& sp) {
		// 防止自我赋值
		if (this != &sp) {
			// 先清除被赋值对象中的资源
			if (_ptr)
				delete _ptr;

			_ptr = sp._ptr;
		}
	}

	T& operator*() {
		return *_ptr;
	}

	T* operator->() {
		return _ptr;
	}

	~SmartPtr() {
		if (_ptr) {
			cout << "析构 释放资源" << _ptr << endl;
			delete _ptr;
			_ptr = nullptr;
		}
	}

private:
	T* _ptr;
};

int div() {
	int a, b;
	cin >> a >> b;
	if (b == 0)
		throw invalid_argument("除0错误");

	return a / b;
}

void Func() {
	//	int* p1 = new int;
	//	int* p2 = new int;

	SmartPtr<int> p1(new int);
	SmartPtr<int> p2(new int);

	cout << div() << endl;
}

class Date {
public:
	~Date() {
		cout << "~Date" << endl;
	}

private:
	int _year = 1;
	int _month = 1;
	int _day = 1;
};

struct ListNode {
	int _data;
	July::weak_ptr<ListNode> _prev;
	July::weak_ptr<ListNode> _next;

	~ListNode() {
		cout << "~ListNode()" << endl;
		cout << endl << endl << endl;
	}
};

int main() {
	std::shared_ptr<Date> sp1(new Date);
	std::shared_ptr<Date> sp2(new Date[10], [](Date* d){ delete [] d; });

	return 0;
}

//int main() {
//	July::shared_ptr<ListNode> node1(new ListNode);
//	July::shared_ptr<ListNode> node2(new ListNode);
//
//	cout << node1.getCount() << endl;
//	cout << node2.getCount() << endl;
//
//	node1->_next = node2;
//	node2->_prev = node1;
//
//	cout << node1.getCount() << endl;
//	cout << node2.getCount() << endl;
//
//	return 0;
//}

//int main() {
////	July::shared_ptr<int> sp1(new int(10));
////	cout << "构造 sp1, sp1:: " << *sp1 << ", pCount:: " << sp1.getCount()
////		 << endl;
////	July::shared_ptr<int> sp2(sp1);
////	cout << "由sp1拷贝构造 sp2, sp2:: " << *sp2
////		 << ", pCount:: " << sp2.getCount() << endl;
////	July::shared_ptr<int> sp3(sp1);
////	cout << "由sp1拷贝构造 sp3, sp3:: " << *sp3
////		 << ", pCount:: " << sp3.getCount() << endl
////		 << endl;
////
////	cout << "更改 *sp2 = 20" << endl;
////	*sp2 = 20;
////	cout << "sp1:: " << *sp1 << ", pCount:: " << sp1.getCount() << endl;
////	cout << "sp2:: " << *sp2 << ", pCount:: " << sp2.getCount() << endl;
////	cout << "sp3:: " << *sp3 << ", pCount:: " << sp3.getCount() << endl << endl;
////
////	July::shared_ptr<int> sp4(new int(44));
////	cout << "构造 sp4, sp4:: " << *sp4 << ", pCount:: " << sp4.getCount()
////		 << endl
////		 << endl;
////
////	sp2 = sp4;
////	cout << "sp4赋值给sp2, sp2:: " << *sp2 << ", pCount:: " << sp2.getCount()
////		 << endl
////		 << endl;
////	cout << "sp1:: " << *sp1 << ", pCount:: " << sp1.getCount() << endl << endl;
////
////	sp4 = sp2;
////	cout << "sp2赋值给sp4, sp4:: " << *sp4 << ", pCount:: " << sp4.getCount()
////		 << endl
////		 << endl;
//
//	std::shared_ptr<int> sp1(new int(10));
//	cout << "构造 sp1, sp1:: " << *sp1 << ", pCount:: " << sp1.use_count()
//		 << endl;
//	std::shared_ptr<int> sp2(sp1);
//	cout << "由sp1拷贝构造 sp2, sp2:: " << *sp2
//		 << ", pCount:: " << sp2.use_count() << endl;
//	std::shared_ptr<int> sp3(sp1);
//	cout << "由sp1拷贝构造 sp3, sp3:: " << *sp3
//		 << ", pCount:: " << sp3.use_count() << endl
//		 << endl;
//
//	cout << "更改 *sp2 = 20" << endl;
//	*sp2 = 20;
//	cout << "sp1:: " << *sp1 << ", pCount:: " << sp1.use_count() << endl;
//	cout << "sp2:: " << *sp2 << ", pCount:: " << sp2.use_count() << endl;
//	cout << "sp3:: " << *sp3 << ", pCount:: " << sp3.use_count() << endl << endl;
//
//	std::shared_ptr<int> sp4(new int(44));
//	cout << "构造 sp4, sp4:: " << *sp4 << ", pCount:: " << sp4.use_count()
//		 << endl
//		 << endl;
//
//	sp2 = sp4;
//	cout << "sp4赋值给sp2, sp2:: " << *sp2 << ", pCount:: " << sp2.use_count()
//		 << endl
//		 << endl;
//	cout << "sp1:: " << *sp1 << ", pCount:: " << sp1.use_count() << endl << endl;
//
//	sp4 = sp2;
//	cout << "sp2赋值给sp4, sp4:: " << *sp4 << ", pCount:: " << sp4.use_count()
//		 << endl
//		 << endl;
//
//	return 0;
//}
//
//int main() {
//    std::auto_ptr<int> ap1(new int);
//    *ap1 = 10;
//    cout << "ap1:: " << *ap1 << endl;
//
//    std::auto_ptr<int> ap2(ap1);
//    cout << "ap1:: " << *ap1 << endl;
//    cout << "ap2:: " << *ap2 << endl;
//
//    return 0;
//}

//int main(){
//	std::unique_ptr<int> up1(new int);
//	*up1 = 20;
//	cout << "up1:: " << *up1 << endl;
//
//	std::unique_ptr<int> up2(up1);
//
//	return 0;
//}
//
//int main() {
//	July::auto_ptr<int> ap1(new int);
//	*ap1 = 10;
//	cout << "ap1:: " << *ap1 << endl;
//
//	July::auto_ptr<int> ap2(ap1);
//	//cout << "ap1:: " << *ap1 << endl;
//	cout << "ap2:: " << *ap2 << endl;
//
//	return 0;
//}

//int main() {
//	try {
//		SmartPtr<int> sp1(new int);
//		SmartPtr<int> sp2 = sp1;
//	}
//	catch (const exception& e) {
//		cout << e.what() << endl;
//	}
//
//	return 0;
//}

//int main() {
//	SmartPtr<int> sp1(new int);
//	*sp1 = 10;
//	cout << *sp1 << endl;
//
//	SmartPtr<Date> sparray(new Date);
//	sparray->_year = 2018;
//	sparray->_month = 1;
//	sparray->_day = 1;
//
//	cout << sparray->_year << "-" << sparray->_month << "-" << sparray->_day
//		 << endl;
//
//	return 0;
//}

//int main() {
//	try {
//		Func();
//	}
//	catch (exception& e) {
//		cout << e.what() << endl;
//	}
//
//	return 0;
//}
